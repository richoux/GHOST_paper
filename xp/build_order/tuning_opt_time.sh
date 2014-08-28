#!/bin/bash

if [ "$#" -ne 3 ]
then
    n=10
else
    n=$3
fi

pvp=(`ls -rS data/good/10k_games/PvP | tail --lines=$n`)
pvt=(`ls -rS data/good/10k_games/PvT | tail --lines=$n`)
pvz=(`ls -rS data/good/10k_games/PvZ | tail --lines=$n`)

for k in {30..90..10}
do
    for i in {1..10}
    do
	for game in "${pvp[@]}"
	do
	    ./bin/experiments_bo data/good/10k_games/PvP/$game $k >> tuning_opt/PvP/$game-$k 
	done
	for game in "${pvt[@]}"
	do
	    ./bin/experiments_bo data/good/10k_games/PvT/$game $k >> tuning_opt/PvT/$game-$k
	done
	for game in "${pvz[@]}"
	do
	    ./bin/experiments_bo data/good/10k_games/PvZ/$game $k >> tuning_opt/PvZ/$game-$k
	done
    done
done

