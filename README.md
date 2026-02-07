# 2 copy, 1 copy, 0 copy sockets implementation

Language: C / Python

Platform: Linux (x86_64)
📖 Overview

This project experimentally evaluates the cost of data movement in network I/O by implementing and comparing three TCP-based client–server communication strategies:
Implementation	Description	Strategy
A1	Standard Baseline	Two-copy socket communication (send/recv)
A2	One-Copy Optimized	Scatter-Gather I/O (sendmsg with iovec)
A3	Zero-Copy	Kernel-bypass optimization (MSG_ZEROCOPY)

The goal is to measure and analyze micro-architectural and application-level performance metrics including throughput, latency, CPU cycles, and context switches.
📂 Project Structure
Plaintext

├── Source Code
│   ├── a1_client.c / a1_server.c   # Baseline Implementation
│   ├── a2_client.c / a2_server.c   # One-Copy Implementation
│   ├── a3_client.c / a3_server.c   # Zero-Copy Implementation
│
├── Scripts
│   ├── Makefile                    # Build system
│   ├── MT25029_Part_C_RunExperiments.sh  # Automation script
│   ├── MT25029_Part_D.py           # Plotting script (Python)
│
└── Output (Generated)
    ├── MT25029_Raw.csv             # Raw experimental data
    └── *.png                       # Performance graphs

⚙️ System Configuration

    CPU: Intel Core i7

    RAM: 16 GB

    OS: Linux (x86_64)

    Kernel: Default Linux distribution kernel

    Network: Localhost TCP Loopback

🚀 Quick Start
1. Build the Project

Clean previous builds and compile all binaries:
Bash

make clean && make

2. Run Experiments (Part C + D)

Execute the automation script. This will run all benchmarks and automatically generate the plots.
Bash

./MT25029_Part_C_RunExperiments.sh

    Note: No manual intervention is required. The script handles compilation, execution, data collection, and plotting.

📊 Methodology & Metrics
Metrics Collected

    Throughput: Application-level (Mbps)

    Latency: Round-trip time (microseconds)

    CPU Cycles: Measured via perf stat

    Context Switches: Measured via perf stat

    Cache Behavior: Measured via perf stat

Experimental Parameters

    Message Sizes: 64 B, 512 B, 4096 B, 65536 B

    Thread Counts: 1, 2, 4, 8

📈 Output Format
CSV Data (MT25029_Raw.csv)

Results are appended automatically in the following format:
Code snippet

impl, msg_size, threads, latency_us, throughput_mbps, cycles, context_switches

Generated Plots

After execution, the following images will be generated:

    throughput.png

    latency.png (Logarithmic scaling)

    context_switches.png

    cycles_per_byte.png

Each plot contains four subplots corresponding to the different message sizes (64, 512, 4096, 65536 bytes).
⚠️ Notes and Limitations

    Localhost Only: Experiments run on loopback; real network behavior (latency/jitter) may differ.

    Permissions: Cache counters and perf stats require appropriate kernel permissions (paranoid level).

    Variability: Absolute values depend heavily on hardware and OS scheduling states at the time of execution.

📝 Conclusion

This project demonstrates the performance impact of different socket communication strategies. By automating the comparison of A1, A2, and A3, we can distinctly observe how threading and message size affect latency, throughput, and scheduling overhead in the Linux kernel.