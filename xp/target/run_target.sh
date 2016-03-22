#!/bin/bash

FILE=max_damage_ratio
MINUTE=$(date +%H_%M)

for i in {1..100}
do
    echo "################" >> results/$(date +%d-%m)/$FILE-$1-$2_$MINUTE.txt
    ./bin/experiments_target $1 $2 >> results/$(date +%d-%m)/$FILE-$1-$2_$MINUTE.txt
    #echo >> results/$FILE
done
