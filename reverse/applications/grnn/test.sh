#!/bin/bash

for (( i = 1; i <= 30; i++ ))
do
    /usr/local/bin/optimizer --source_type java_class --output final_java_class --directory java_data  &> test_$i.log
done
