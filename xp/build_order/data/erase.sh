#!/bin/bash

for i in $(ls -l $1 | grep -E " 2 ")
do
    if [[ $i == *short* ]]
    then
	rm -f $1/$i
    fi
done
