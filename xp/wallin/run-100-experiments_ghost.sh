#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 time_limit attempts path" >&2
  exit 1
fi

for i in {1..100}
do
    echo \*\*\*\*\*\*\*\*\*\*\*\* | cat >> $1/gap_100_tabu_runs_20_1_tabu-$2
    echo \*\*\*\* $i \*\*\*\* | cat >> $1/gap_100_tabu_runs_20_1_tabu-$2
    echo \*\*\*\*\*\*\*\*\*\*\*\* | cat >> $1/gap_100_tabu_runs_20_1_tabu-$2
    ./run-experiments_ghost.sh 20 $2 >> $1/gap_100_tabu_runs_20_1_tabu-$2
done
