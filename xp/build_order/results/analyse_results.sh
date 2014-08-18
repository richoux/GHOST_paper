#!/bin/bash

for i in $(ls $1/$2/*)
do
    ./analyse_results.rb $i >> $1/$2.all
done
./analyse_mean.rb $1/$2.all
