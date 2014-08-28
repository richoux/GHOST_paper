#!/bin/bash

file=( `cat "good.txt" `)

for i in ${file[@]}
do
    IFS='/' read -a filename <<< "$i"
    mv 10k_games/$i* good/10k_games/"${filename[0]}"/
    mv 5min_games/$i* good/5min_games/"${filename[0]}"/
done
