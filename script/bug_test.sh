cd ../bui
#make
data_dir="/data/liujie/gqr/data"
out_dir="/data/sydeng/repositary/hnsw-repo/testOut"
hnsw_dir="/data/sydeng/repositary/hnsw-repo"
mode_code=0
data_set="sift1m"
#metric="euclid"
#topk=20
# gdb --args \
mpirun -np 12 --hostfile host_file ./bug \
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
    --hnsw_dir ${out_dir}/${data_set}/hnsw \
    --subset_dir ${out_dir}/${data_set}/subset \
    --centroids_file ${out_dir}/${data_set}/centroids \
    --mode_code ${mode_code}

