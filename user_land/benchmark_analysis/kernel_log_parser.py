#!/usr/bin/env python3

import re
import sys

case_name = ["1 Proc 64 MB", "1 Proc 128 MB", "4 Proc 64 MB", "4 Proc 128 MB"]

def parse_file(data):
    current_case = -1
    lst_mmmax = 0
    for line in data:
        if line.startswith("[NEW_OOM]"):
            x = re.search("uRSS=(.*?), mm_max=(.*?),", line)
            if x:
                urss = int(x.group(1))
                mmmax = int(x.group(2))
                if lst_mmmax != mmmax:
                    current_case += 1
                    lst_mmmax = mmmax
                print(f"{name},{case_name[current_case]},{urss},{mmmax}")

path = sys.argv[1]
name = sys.argv[2]

with open(path, "r") as f:
    parse_file(f.readlines())
