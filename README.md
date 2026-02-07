# 2-Copy, 1-Copy, and 0-Copy Socket Implementation

**Language:** C, Python  
**Platform:** Linux (x86_64)

---

## 📖 Overview

This project experimentally evaluates the cost of data movement in network I/O by implementing and comparing three TCP-based client–server communication strategies:

| Implementation | Description         | Strategy |
|---------------|---------------------|----------|
| **A1** | Standard Baseline | Two-copy socket communication (`send` / `recv`) |
| **A2** | One-Copy Optimized | Scatter–Gather I/O (`sendmsg` with `iovec`) |
| **A3** | Zero-Copy | Kernel-assisted zero-copy (`MSG_ZEROCOPY`) |

The goal is to measure and analyze both micro-architectural and application-level performance metrics, including throughput, latency, CPU cycles, and context switches.

---

## ⚙️ System Configuration

- **CPU:** Intel Core i7  
- **RAM:** 16 GB  
- **OS:** Linux (x86_64)  
- **Kernel:** Default Linux distribution kernel  
- **Network:** TCP over localhost (loopback)

---

## 🚀 Quick Start

### 1. Build the Project

Clean previous builds and compile all binaries:

```bash
make clean && make

2. Run Experiments (Part C + Part D)

Run the automation script to execute all benchmarks and generate plots:

./MT25029_Part_C_RunExperiments.sh

    Note: No manual intervention is required. The script handles compilation, execution, data collection, and plotting.

📊 Methodology & Metrics
Metrics Collected

    Throughput: Application-level throughput (Mbps)

    Latency: Round-trip time (µs)

    CPU Cycles: Measured using perf stat

    Context Switches: Measured using perf stat

    Cache Behavior: Measured using perf stat

Experimental Parameters

    Message Sizes: 64 B, 512 B, 4096 B, 65536 B

    Thread Counts: 1, 2, 4, 8

📈 Output Format
CSV Data (MT25029_Raw.csv)

Results are automatically appended in the following format:

impl,msg_size,threads,latency_us,throughput_mbps,cycles,context_switches

Generated Plots

After execution, the following plots are generated:

    throughput.png

    latency.png (logarithmic scale)

    context_switches.png

    cycles_per_byte.png

Each plot contains four subplots, corresponding to message sizes:

    64 B

    512 B

    4096 B

    65536 B

⚠️ Notes and Limitations

    Localhost Only: Experiments run on loopback; real network latency and jitter are not represented.

    Permissions: Access to cache counters and perf statistics may require lowering the kernel perf_event_paranoid level.

    Variability: Absolute performance values depend on hardware characteristics and OS scheduling state at runtime.

📝 Conclusion

This project demonstrates the performance impact of different socket communication strategies in Linux. By automating the comparison of A1 (two-copy), A2 (one-copy), and A3 (zero-copy) approaches, the experiments highlight how message size and thread count influence latency, throughput, and kernel scheduling overhead.

