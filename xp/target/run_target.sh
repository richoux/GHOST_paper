#!/bin/bash

FILE=max_damage

for i in {1..100}
do
    echo "################" >> results/$(date +%d-%m)/$FILE-$1-$2.txt
    ./bin/experiments_target $1 $2 >> results/$(date +%d-%m)/$FILE-$1-$2.txt
    #echo >> results/$FILE
done
