#!/bin/bash
# MT25029

SIZES="64 512 4096 65536"
THREADS="1 2 4 8"

MASTER="MT25029_Part_C_Raw.csv"

make clean && make
rm -f $MASTER

echo "impl,msg_size,threads,latency_us,throughput_mbps,cycles,cache_misses,l1_misses,context_switches" > $MASTER

for impl in A1 A2 A3; do

  ./a${impl#A}_server 4096 &
  SERVER_PID=$!
  sleep 2

  for s in $SIZES; do
    for t in $THREADS; do

      echo "Running $impl size=$s threads=$t"

      TMP=$(mktemp)

      perf stat -e cycles,cache-misses,L1-dcache-load-misses,context-switches \
        ./a${impl#A}_client 127.0.0.1 9090 $s $t \
        2>&1 | tee $TMP

      lat=$(grep LATENCY_US $TMP | cut -d= -f2)
      thr=$(grep THROUGHPUT_MBPS $TMP | cut -d= -f2)

      cycles=$(grep cycles $TMP | head -n1 | sed 's/,//g' | awk '{print $1}')
      cache=$(grep cache-misses $TMP | head -n1 | sed 's/,//g' | awk '{print $1}')
      l1=$(grep L1-dcache-load-misses $TMP | head -n1 | sed 's/,//g' | awk '{print $1}')
      ctx=$(grep context-switches $TMP | head -n1 | sed 's/,//g' | awk '{print $1}')

      echo "$impl,$s,$t,$lat,$thr,$cycles,$cache,$l1,$ctx" >> $MASTER

      rm $TMP
      sleep 1

    done
  done

  kill -9 $SERVER_PID
  sleep 2

done

echo "Done → $MASTER"
