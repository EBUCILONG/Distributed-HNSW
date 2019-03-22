#!/bin/bash


for program in parhip edge_list_to_metis_graph friendster_list_to_metis_graph graph2binary graph2binary_external readbgf toolbox dspac; do
scons program=$program variant=optimized -j 16
if [ "$?" -ne "0" ]; then 
        echo "compile error in $program. exiting."
        exit
fi
done
cd interface;
scons variant=optimized -j 16

rm config.log
