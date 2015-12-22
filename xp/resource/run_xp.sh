#!/bin/bash

FILE=$3
DATE=$(date +%y_%m_%d)
for i in {1..100}
do
    echo "################" >> xp/$FILE-$1-$2_$DATE.txt
    ./ghost $1 $2 $3 >> xp/$FILE-$1-$2_$DATE.txt
    #echo >> results/$FILE
done
