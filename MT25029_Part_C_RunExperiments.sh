#!/bin/bash
# MT25029 Final Part C

SIZES="64 512 4096 65536"
THREADS="1 2 4 8"

MASTER="MT25029_Raw.csv"

make clean && make
rm -f $MASTER

echo "impl,msg_size,threads,latency_us,throughput_mbps,cycles,context_switches" > $MASTER

for impl in A1 A2 A3; do

  ./a${impl#A}_server &
  SERVER_PID=$!
  sleep 2

  for s in $SIZES; do
    for t in $THREADS; do

      echo "Running $impl size=$s threads=$t"

      TMP=$(mktemp)

      perf stat ./a${impl#A}_client 127.0.0.1 9090 $s $t 2>&1 | tee $TMP

      latency=$(grep LATENCY_US $TMP | cut -d= -f2)
      thr=$(grep THROUGHPUT_MBPS $TMP | cut -d= -f2)

      cycles=$(grep -m1 " cycles" $TMP | awk '{print $1}' | tr -d ',')
      ctx=$(grep -m1 "context-switches" $TMP | awk '{print $1}' | tr -d ',')

      echo "$impl,$s,$t,$latency,$thr,$cycles,$ctx" >> $MASTER

      rm $TMP
      sleep 1

    done
  done

  kill $SERVER_PID
  sleep 2

done

echo "Done. Results in $MASTER"
