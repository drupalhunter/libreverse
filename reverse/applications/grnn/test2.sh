#!/bin/bash

for (( i = 1; i <= 30; i++ ))
do
    data=`/usr/local/bin/grnn_optimizer --source_type windows_pe --output final --directory pe_data`
    data=$i,$data
    echo $data
done
