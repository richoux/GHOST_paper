#!/bin/bash

./pgm.sh 20 30
./run-experiments_bo.sh 10k_games/PvP 20 30
./run-experiments_bo.sh 10k_games/PvT 20 30
./run-experiments_bo.sh 10k_games/PvZ 20 30
./run-experiments_bo.sh 7.8k_games/PvP 20 30
./run-experiments_bo.sh 7.8k_games/PvT 20 30
./run-experiments_bo.sh 7.8k_games/PvZ 20 30

cd results/pgm/
mv 10k/*7800* 7.8k/
cd ..
./analyse_results.sh pgm 10k
./analyse_results.sh pgm 7.8k
./analyse_results.sh reloaded/10k_games PvP
./analyse_results.sh reloaded/10k_games PvT
./analyse_results.sh reloaded/10k_games PvZ
./analyse_results.sh reloaded/7.8k_games PvP
./analyse_results.sh reloaded/7.8k_games PvT
./analyse_results.sh reloaded/7.8k_games PvZ
