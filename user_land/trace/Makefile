trace: trace.cpp
	g++ $< -o $@ -O2

run: trace
	sudo ./$<

test: test.cpp
	g++ $< -o $@

run_test: test
	./$<
