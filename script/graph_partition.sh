cd ../bui
make
data_dir="/data/liujie/gqr/data"
out_dir="/data/sydeng/repositary/hnsw-repo/testOut/"
data_set="sift1m"
#metric="euclid"
#topk=20
# gdb --args \
../bui/sift1k \
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

