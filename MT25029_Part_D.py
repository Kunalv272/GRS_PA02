# MT25029
import matplotlib.pyplot as plt

threads=[1,2,4,8]
sizes=[64,512,4096,65536]
labels=["A1","A2","A3"]

# ---------------- HARD CODED DATA ----------------

latency={
64:(
[0.023671,0.026562,0.026626,0.031420],
[0.028219,0.028833,0.033433,0.035593],
[0.026670,0.027830,0.030529,0.038906]),

512:(
[0.192013,0.191937,0.229390,0.262086],
[0.212266,0.235280,0.240783,0.292818],
[0.213044,0.213435,0.228180,0.283366]),

4096:(
[1.572703,1.684799,2.067233,2.047480],
[1.850270,1.824476,2.026320,2.410178],
[1.618006,1.554539,1.724209,1.991611]),

65536:(
[26.788574,27.865050,29.219934,39.903575],
[32.323233,32.109039,32.808888,34.858943],
[26.481696,28.411131,27.528422,33.213881])
}

throughput={
64:(
[21630,19275,19229,16295],
[18143,17757,15314,14384],
[19197,18397,16770,13159]),

512:(
[21331,21340,17856,15628],
[19296,17409,17011,13988],
[19226,19190,17950,14454]),

4096:(
[20835,19449,15851,16004],
[17709,17960,16171,13595],
[20252,21078,19004,16453]),

65536:(
[19571,18815,17942,13138],
[16220,16328,15980,15040],
[19798,18453,19045,15785])
}

context={
64:(
[205231,380127,684955,922325],
[162969,347498,540277,802281],
[172034,360160,587735,711551]),

512:(
[183039,405776,617976,851938],
[183929,339054,576112,799787],
[170609,383893,637676,925355]),

4096:(
[172397,383559,565021,836723],
[162934,345206,553515,782791],
[180697,408233,644836,929838]),

65536:(
[183538,378461,621121,741318],
[148845,321873,552924,798797],
[182046,323207,653180,924149])
}

cycles={
64:[4428434960,3746313929,3921583313],
512:[4231862951,3915314230,3842335182],
4096:[4405385392,3677941373,4182665315],
65536:[3920243378,3504580704,4083401364]
}

# ---------------- GENERIC GRID ----------------

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
    fig.suptitle(title+"\nSystem: Core i7, 16GB RAM, Linux",fontsize=14)
    plt.tight_layout()
    plt.savefig(filename,dpi=300)
    plt.show()

# ---------------- PLOTS ----------------

plot_grid(throughput,"Throughput vs Threads","Mbps","throughput.png")

plot_grid(latency,"Latency vs Threads","Microseconds","latency.png",log=True)

plot_grid(context,"Context Switches vs Threads","Count","context.png")

# Cycles per byte

fig,axs=plt.subplots(2,2,figsize=(12,8))
for ax,size in zip(axs.flat,sizes):
    vals=[cycles[size][i]/size for i in range(3)]
    ax.bar(labels,vals)
    ax.set_title(f"{size} bytes")
    ax.set_ylabel("Cycles/Byte")
    ax.grid(axis='y')

fig.suptitle("CPU Cycles per Byte\nSystem: Core i7, Linux")
plt.tight_layout()
plt.savefig("cycles.png",dpi=300)
plt.show()
