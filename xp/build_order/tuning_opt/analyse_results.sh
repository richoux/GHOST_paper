#!/bin/bash

for k in {100..1000..100}
do
    for i in $(ls PvP/*-$k)
    do
	./analyse_results.rb $i >> PvP-$k.all
    done
    ./analyse_mean.rb PvP-$k.all

    for i in $(ls PvT/*-$k)
    do
	./analyse_results.rb $i >> PvT-$k.all
    done
    ./analyse_mean.rb PvT-$k.all

    for i in $(ls PvZ/*-$k)
    do
	./analyse_results.rb $i >> PvZ-$k.all
    done
    ./analyse_mean.rb PvZ-$k.all
done
