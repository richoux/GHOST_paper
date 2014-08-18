#!/bin/bash

for i in $(ls data/$1/*)
do
    IFS='/' read -a filename <<< "$i"
    for k in {1..10}
    do
	./bin/experiments_bo $i >> results/dave_timeouts/$1/"${filename[-1]}"
	echo >> results/dave_timeouts/$1/"${filename[-1]}"
    done
done



