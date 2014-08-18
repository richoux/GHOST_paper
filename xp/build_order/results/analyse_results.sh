#!/bin/bash

for i in $(ls $1/*)
do
    ./analyse_results.rb $i >> $1.all
done
./analyse_mean.rb $1.all
