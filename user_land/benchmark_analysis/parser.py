#!/usr/bin/env python3

import re
import sys

def parse_time(data):
    data.split(" ")
    x = re.search("(.*?)m(.*?)s", data)
    m, s = x.group(1), x.group(2)
    return int(m) * 60 + float(s)

def parse_time_output(data):
    data = data.split("    ")
    return (parse_time(data[1]), parse_time(data[2]), parse_time(data[3]))

def parse_parameter(data):
    x = re.search("process=(.*?) mem=(.*?) epoch=(.*)", data)
    return (int(x.group(1)), int(x.group(2)), int(x.group(3)))

def parse_file(data):
    for i in range(0, len(data), 2):
        process, mem, epoch = parse_parameter(data[i])
        real, user, system = parse_time_output(data[i + 1])
        print(f"{name}, {type_order}, {process}, {mem}, {epoch},Real, {real}")
        print(f"{name}, {type_order}, {process}, {mem}, {epoch},User, {user}")
        print(f"{name}, {type_order}, {process}, {mem}, {epoch},System, {system}")
        print(f"{name}, {type_order}, {process}, {mem}, {epoch},All, {system + user}")

path = sys.argv[1]
name = sys.argv[2]
type_order = sys.argv[3]

with open(path, "r") as f:
    parse_file(f.readlines())
