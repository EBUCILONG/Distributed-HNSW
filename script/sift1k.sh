cd ../bui
make
data_dir="/data/sydeng/data"
data_set="siftsmall"
#metric="euclid"
#topk=20
# gdb --args \
../bui/sift1k \
    -p 100 \
    --max_balance 4 \
    -i 100 \
    -e ./cluster_result \
    -t ${data_dir}/${data_set}/${data_set}_base.fvecs \
    -b ${data_dir}/${data_set}/${data_set}_base.fvecs \
    -q ${data_dir}/${data_set}/${data_set}_query.fvecs  \
    -g ${data_dir}/${data_set}/${topk}_${data_set}_${metric}_groundtruth.lshbox \
    --kmeans_centers 20
