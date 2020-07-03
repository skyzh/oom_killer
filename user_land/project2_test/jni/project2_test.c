#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <signal.h>

void test1() {
    printf("@@@@uid: %d\n", getuid());
    printf("@@@@pid: %d\n", getpid());
}

int main(int argc, char **argv) {
  struct passwd *pwd_struct = getpwnam(argv[1]);
  if (!pwd_struct) {
    printf("Failed to fetch passwd struct\n");
    return -1;
  }
  printf("pw->uid=%d, pw->name=%s\n", pwd_struct->pw_uid, pwd_struct->pw_name);

  int limit = atoi(argv[2]);
  pid_t *pids = (pid_t*)malloc((argc-3)*sizeof(pid_t));
  syscall(378, pwd_struct->pw_uid, limit);
  int i, mem;
  test1();
  for (i = 3; i < argc; ++i) {
     mem = atoi(argv[i]);
     pid_t p = pids[i-3] = fork();
     if (0 == p) {
        printf("child process start malloc: pid=%d, uid=%d, mem=%d\n", getpid(), getuid(), mem);
        char *m = (char*)malloc(mem);
        //memset(m, 0, mem);
        int j = 0;
        for (j = 0; j < mem; ++j) {
            m[j] = '\0';
        }
        printf("child process finish malloc: pid=%d, uid=%d, mem=%d\n", getpid(), getuid(), mem);
        return 0;
     }
  }

  for (i = 0; i < argc-3; ++i) {
    waitpid(pids[i], NULL, 0);
  }

  return 0;
}

