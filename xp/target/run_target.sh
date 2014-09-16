#!/bin/bash

FILE=max_damage-bis.txt

for i in {1..100}
do
    echo "################" >> results/$FILE
    ./bin/experiments_target 13 30 >> results/$FILE
    #echo >> results/$FILE
done
