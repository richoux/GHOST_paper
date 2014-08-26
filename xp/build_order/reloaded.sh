#!/bin/bash

for k in {1..10}
do
    ./bin/experiments_bo data/PvT/TL954.rep.rgd.short >> results/reloaded/TL954
    echo >> results/reloaded/TL954

    ./bin/experiments_bo data/PvT/GG26110.rep.rgd.short >> results/reloaded/GG26110
    echo >> results/reloaded/GG26110
done



