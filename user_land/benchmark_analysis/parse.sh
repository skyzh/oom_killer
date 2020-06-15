#!/bin/bash
echo "Type, TypeOrder, Process, Memory, Epoch, TimeType, Time" > result.csv
./parser.py ../benchmark/result/goldfish_3.4.out Unmodified 1 >> result.csv
# ./parser.py ../benchmark/result/oom_killer_with_limit.out "OOM Killer With Limit" >> result.csv
./parser.py ../benchmark/result/oom_killer_disabled.out "OOM Killer Disabled" 2 >> result.csv
# ./parser.py ../benchmark/result/oom_killer_enabled.out "OOM Killer Enabled" 3  >> result.csv
./parser.py ../benchmark/result/oom_killer_with_limit.out "OOM Killer Enabled" 3  >> result.csv
./parser.py ../benchmark/result/oom_killer_trivial.out "Trivial OOM Killer" 4  >> result.csv

echo "Type, Case, RSS, Limit" > result_overcommit.csv
./kernel_log_parser.py ../benchmark/result/kernel_log_trivial.txt Trivial >> result_overcommit.csv
./kernel_log_parser.py ../benchmark/result/kernel_log_timer.txt Timer >> result_overcommit.csv
./kernel_log_parser.py ../benchmark/result/kernel_log_notifier.txt "New OOM Killer" >> result_overcommit.csv
