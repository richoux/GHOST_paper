#!/bin/bash

for i in $(ls data/PGM_replays/extract/*)
do
    IFS='/' read -a filename <<< "$i"
    for k in {1..10}
    do
	./bin/experiments_bo $i $1 $2 >> results/pgm/10k/"${filename[-1]}"-$1-$2
	echo >> results/pgm/10k/"${filename[-1]}"-$1-$2
    done
done



