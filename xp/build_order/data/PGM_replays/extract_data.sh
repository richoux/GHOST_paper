#!/bin/bash

for i in $(ls Protoss/data/*)
do
    IFS='/' read -a filename <<< "$i"
    ./extract_data.rb $i $1 >> extract/"${filename[-1]}"-$1
done
