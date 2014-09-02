#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 time_limit attempts path" >&2
  exit 1
fi

for i in {1..100}
do
    echo \*\*\*\*\*\*\*\*\*\*\*\* | cat >> $1/sat_100_20_1
    echo \*\*\*\* $i \*\*\*\* | cat >> $1/sat_100_20_1
    echo \*\*\*\*\*\*\*\*\*\*\*\* | cat >> $1/sat_100_20_1
    ./run-experiments_ghost.sh 20 8 >> $1/sat_100_20_1
done
