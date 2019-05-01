#!/usr/bin/env bash

OUTPUT_PATH=/data/sydeng/repositary/hnsw-repo/testOut/deep1b-10m/10000/subfile/concated
INPUT_PATH=/data/sydeng/repositary/hnsw-repo/testOut/deep1b-10m/10000/subfile

onexit () {
    echo "Aborting..."
    if pkill -P $$; then echo "Killed all sub processes"
    else echo "Failed to clean up sub processes."
    fi
    trap SIGINT
    exit
}

echo Confirm output path $OUTPUT_PATH
echo Confirm input path $INPUT_PATH

trap "onexit" SIGINT

for ((i=0, partitionNum=10; i<partitionNum; i++))
do
    echo "[PART-$i] Concatenating partition $i out of" $((partitionNum-1)) && \
    output_file=$OUTPUT_PATH/partition$i && \
    for ((j=0, subfileNum=10; j<subfileNum; j++))
    do
        input_file=$INPUT_PATH/w$j/partition$i && \
        echo "[PART-$i] Processing subfile w$j/partition$i" && sleep 1
        cat $input_file >> $output_file
    done &
done
wait
echo "All tasks completed."
trap SIGINT