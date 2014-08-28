#!/bin/bash

if [ "$#" -ne 3 ]
then
    n=10
else
    n=$3
fi

list=(`ls -rS ../data/$2 | tail --lines=$n`)

for game in "${list[@]}"
do
    ./analyse_results.rb $1/$2/$game >> tmp
done
./analyse_mean.rb tmp
rm tmp

