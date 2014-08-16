#!/bin/bash

for i in $(ls bo*)
do
    echo $i
    ./analyse.rb $i
    echo 
done
