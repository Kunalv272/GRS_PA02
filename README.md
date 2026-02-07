Programming Assignment – Network I/O Performance Evaluation

Roll Number: MT25029

Overview

This project experimentally evaluates the cost of data movement in
network I/O by implementing and comparing three TCP-based client–server
communication strategies:

A1: Standard two-copy socket communication A2: One-copy optimized socket
communication A3: Zero-copy socket communication

The goal is to measure and analyze micro-architectural and
application-level performance metrics such as throughput, latency, CPU
cycles, cache behavior, and context switches.

Metrics Collected

Throughput (Mbps) – Application-level Latency (microseconds) –
Application-level CPU cycles – perf stat Context switches – perf stat
Cache behavior – perf stat

System Configuration

CPU: Intel Core i7 RAM: 16 GB Operating System: Linux (x86_64) Kernel:
Default Linux distribution kernel Network: localhost TCP

Project Structure

a1_client.c a1_server.c a2_client.c a2_server.c a3_client.c a3_server.c
Makefile MT25029_Part_C_RunExperiments.sh MT25029_Part_D.py
MT25029_Raw.csv README.txt

Generated after execution: throughput.png latency.png
context_switches.png cycles_per_byte.png

Build Instructions

Run: make clean && make

The clean target removes binaries, CSV files, and generated plots to
ensure fresh experiments.

Running Experiments (Part C + D)

Execute: ./MT25029_Part_C_RunExperiments.sh

This single script: - Compiles all implementations - Runs experiments
across message sizes and thread counts - Collects perf profiling data -
Generates MT25029_Raw.csv - Automatically invokes the Python plotting
script

No manual intervention is required.

CSV Output

Results are stored in MT25029_Raw.csv with format:

impl,msg_size,threads,latency_us,throughput_mbps,cycles,context_switches

Plot Generation (Part D)

After Part C completes, MT25029_Part_D.py is executed automatically to
generate:

throughput.png latency.png context_switches.png cycles_per_byte.png

Each plot contains four subplots (64, 512, 4096, 65536 bytes) comparing
A1, A2, and A3. Latency plots use logarithmic scaling.

Experimental Methodology

Message sizes: 64, 512, 4096, 65536 bytes Thread counts: 1, 2, 4, 8

Servers are restarted per implementation. Measurements are collected via
perf stat. Results are appended automatically to CSV. Plots are
generated directly from collected data.

Reproducibility

Run: make clean && make ./MT25029_Part_C_RunExperiments.sh

This regenerates all results and plots from scratch.

Notes and Limitations

Experiments run on localhost; real network behavior may differ. Cache
counters depend on kernel perf permissions. Absolute values depend on
hardware and OS scheduling.


Client/server implementations (A1/A2/A3) Automated Part C script CSV
results Plotting script (Part D) Generated graphs README documentation

Conclusion

This project demonstrates the performance impact of different socket
communication strategies and shows how threading and message size affect
latency, throughput, and scheduling overhead. Automated experimentation
enables systematic comparison across implementations.