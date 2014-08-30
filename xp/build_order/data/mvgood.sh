#!/bin/bash

file=( `cat "good.txt" `)

for i in ${file[@]}
do
    IFS='/' read -a filename <<< "$i"
    #mv 10k_games/$i* good/10k_games/"${filename[0]}"/
    mv 7.8k_games/$i* good/7.8k_games/"${filename[0]}"/
done
