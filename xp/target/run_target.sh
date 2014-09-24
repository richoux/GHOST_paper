#!/bin/bash

FILE=max_kill

for i in {1..100}
do
    echo "################" >> results/24-09/$FILE-$1-$2.txt
    ./bin/experiments_target $1 $2 >> results/24-09/$FILE-$1-$2.txt
    #echo >> results/$FILE
done
