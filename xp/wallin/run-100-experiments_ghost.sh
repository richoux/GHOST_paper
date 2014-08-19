#!/bin/bash

if [ "$#" -ne 3 ]; then
  echo "Usage: $0 time_limit attempts path" >&2
  exit 1
fi

for i in `seq 1 100`; do
    echo \*\*\*\*\*\*\*\*\*\*\*\* | cat >> $3/gap_d92126c5853f529c92bebbaf2bd268bcb13e07a1_100_runs_$1_$2
    echo \*\*\*\* $i \*\*\*\* | cat >> $3/gap_d92126c5853f529c92bebbaf2bd268bcb13e07a1_100_runs_$1_$2
    echo \*\*\*\*\*\*\*\*\*\*\*\* | cat >> $3/gap_d92126c5853f529c92bebbaf2bd268bcb13e07a1_100_runs_$1_$2
    ./run-experiments_ghost.sh $1 $2 >> $3/gap_d92126c5853f529c92bebbaf2bd268bcb13e07a1_100_runs_$1_$2
done