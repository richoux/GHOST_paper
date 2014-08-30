#!/bin/bash

for i in $(ls $1/*rgd)
do
    IFS='.' read -a filename <<< "$i"
    grep -E "((Created|Morph|FinishUpgrade|FinishResearch).(.*Protoss|Singularity|Leg|Scarab|Reaver|Gravitic|Apial|Carrier|Argus|Disruption|Psionic|Hallucination|Khaydarin|Maelstrom|Mind Control|Sensor Array|Recall|Stasis Field))" $i > Protoss/"${filename[0]}".short
done
