#!/bin/bash

for s in {10..100..5}
do
    for o in {100..1000..50}
    do
	for i in {1..10}
	do
	    /home/flo/ghost/bin/ghost $s $o >> bo_$s-$o
	done
    done
done

