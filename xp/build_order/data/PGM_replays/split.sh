#!/bin/bash

for i in $(ls *short)
do
    grep '^[0-9]*,'$1 $i > $i.player$1
done
