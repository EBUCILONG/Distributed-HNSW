#!/usr/bin/env bash
cd ../bui
#make
data_dir="/data/liujie/gqr/data"
out_dir="/data/sydeng/repositary/hnsw-repo/testOut"
hnsw_dir="/data/sydeng/repositary/hnsw-repo/testOut/sift1m/hnsw"
map_address="/data/sydeng/repositary/hnsw-repo/testOut/sift1m/map"

zookeeper_hosts="w2:2181"
broker_list="w3:9092"

data_set="sift1m"
metric="euclid"

#para that will not change for a graph and dataset
num_subhnsw=10
num_centroid=1000
data_dim=128

#para for multithread
num_worker=2

#para that may change frequently
topk=10
wake_up_controller=10
sender_ef=10
slave_ef=10

# gdb --args \

./start_evaluator \
    -p 1000 \
    --max_balance 4 \
    -i 100 \
    --load_cluster 1 \
    -o ${out_dir}${data_set}/ \
    -c ${out_dir}/${data_set}/${data_set}_cluster_result \
    --graph_file ${out_dir}/${data_set}/${data_set}_graph \
    -t ${data_dir}/${data_set}/${data_set}_base.fvecs \
    -b ${data_dir}/${data_set}/${data_set}_base.fvecs \
    -q ${data_dir}/${data_set}/${data_set}_query.fvecs  \
    -g ${data_dir}/${data_set}/${topk}_${data_set}_${metric}_groundtruth.lshbox \
    --sender_ef ${sender_ef} \
    --slave_ef ${slave_ef}  \
    --zookeeper_hosts ${zookeeper_hosts}    \
    --broker_list ${broker_list}    \
    --dim ${data_dim}   \
    --num_centroid ${num_centroid}  \
    --num_subhnsw ${num_subhnsw}    \
    --wakeup_rate ${wake_up_controller}    \
    --hnsw_dir ${hnsw_dir}  \
    --map_address ${map_address}    \
    --top_k ${topk}   \
    --num_worker ${num_worker}



