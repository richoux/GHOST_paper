#!/bin/bash

for i in {0..25}
do
    for k in {1..10}
    do
	./bin/experiments_bo data/PvT/TL954.rep.rgd.short $i >> results/tabu/TL954/TL954-$i
	echo >> results/tabu/TL954/TL954-$i
    done
done



