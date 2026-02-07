import matplotlib.pyplot as plt

threads = [1,2,4,8]
sizes = [64,512,4096,65536]

# ---------------- DATA ----------------

latency = {
64: ([2000.323,1000.1085,500.07575,250.07725],
     [2000.22,1000.144,500.0745,250.06225],
     [2000.383,1000.1415,500.17925,250.04225]),

512: ([2000.169,1000.1105,500.048,250.046375],
      [2000.187,1000.162,500.06625,250.150625],
      [2000.194,1000.1615,500.06475,250.17175]),

4096: ([2000.228,1000.1155,500.09575,250.157375],
       [2000.195,1000.082,500.077,250.054],
       [2000.466,1000.1445,500.05875,250.060625]),

65536: ([2000.221,1000.1005,500.077,250.061875],
        [2000.2,1000.0945,500.07475,250.0565],
        [2000.196,1000.265,500.09525,250.16075])
}

throughput = {
64: ([861,598,297,295],[703,749,322,277],[741,668,333,273]),
512: ([5542,3748,2154,2078],[4888,3290,2223,2250],[5144,3431,2153,2222]),
4096: ([31774,18849,13909,14470],[28610,17407,14060,13708],[25705,19169,13990,13839]),
65536: ([51923,48240,42976,42693],[53289,49634,43563,41258],[58213,49643,44830,42255])
}

context = {
64: ([549,221793,492018,906375],[351,129653,481064,842545],[506,138931,483636,830808]),
512: ([2859,228632,513023,844803],[2036,224361,489481,908261],[2636,229307,471238,897538]),
4096: ([18143,218972,532970,842888],[23586,224998,562578,807824],[24600,237055,526597,844232]),
65536: ([98545,334415,500792,566598],[102307,357904,512668,494204],[110223,362340,517588,515872])
}

cycles = {
64: [7597719075,7646814106,7935743429],
512: [7101181051,7132276413,7526340800],
4096: [7375138739,7115427744,6944834240],
65536: [4703647727,4809886952,5127745030]
}

labels=["A1","A2","A3"]

# ---------------- PLOTTING FUNCTION ----------------

def plot_grid(data,title,ylabel,filename,log=False):
    fig,axs=plt.subplots(2,2,figsize=(12,8))
    for ax,size in zip(axs.flat,sizes):
        for i in range(3):
            ax.plot(threads,data[size][i],marker='o',label=labels[i])
        ax.set_title(f"{size} bytes")
        ax.set_xlabel("Threads")
        ax.set_ylabel(ylabel)
        if log: ax.set_yscale("log")
        ax.grid()
        ax.legend()
    fig.suptitle(title+"\nSystem: Linux x86_64 localhost TCP",fontsize=14)
    plt.tight_layout()
    plt.savefig(filename,dpi=300)
    plt.show()

# ---------------- RUN ----------------

plot_grid(throughput,"Throughput vs Threads","Mbps","throughput.png")

plot_grid(latency,"Latency vs Threads","Microseconds","latency.png",log=True)

plot_grid(context,"Context Switches vs Threads","Count","context_switches.png")

# Cycles per byte

fig,axs=plt.subplots(2,2,figsize=(12,8))
for ax,size in zip(axs.flat,sizes):
    vals=[cycles[size][i]/size for i in range(3)]
    ax.bar(labels,vals)
    ax.set_title(f"{size} bytes")
    ax.set_ylabel("Cycles/Byte")
    ax.grid(axis='y')

fig.suptitle("CPU Cycles per Byte\nSystem: Linux x86_64 localhost TCP")
plt.tight_layout()
plt.savefig("cycles_per_byte.png",dpi=300)
plt.show()
