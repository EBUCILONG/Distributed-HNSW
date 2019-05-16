#!/usr/bin/env bash

script_path=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/script
workers=(w1 w2 w3 w4 w5)

num_subhnsw=${#workers[@]}

onexit () {
    echo "Aborting..."
    if pkill -P $$; then echo "Killed all sub processes"
    else echo "Failed to clean up sub processes."
    fi
    trap SIGINT
    exit
}

echo Training ${num_subhnsw} hnsws

trap "onexit" SIGINT

for ((i=0; i<num_subhnsw; i++))
do
    ssh ${workers[$i]} "cd ${script_path}; echo \"[$i] Running idvecs_hnsw $i out of\" $((num_subhnsw-1)) && ./idvecs_hnsw.sh $i" &
    echo "Finished sending command on " ${workers[$i]}
done
wait
echo "All tasks completed."
trap SIGINT