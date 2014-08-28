#!/bin/bash

for i in $(ls data/good/$1/*)
do
    IFS='/' read -a filename <<< "$i"
    for k in {1..10}
    do
	./bin/experiments_bo $i >> results/reloaded/$1/"${filename[-1]}"
	echo >> results/reloaded/$1/"${filename[-1]}"
    done
done



