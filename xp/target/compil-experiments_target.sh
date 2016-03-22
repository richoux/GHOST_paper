#!/bin/bash
GHOST=/home/flo/Seafile/Recherche/Programmes/GHOST
OPT=-O3

rm ./bin/experiments_target -f

# debug mode without trace 
#g++ -g -std=c++11 $OPT -DNDEBUG experiments/main_target.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/unit.cpp $GHOST/src/misc/unitMap.cpp $GHOST/src/domains/targetSelectionDomain.cpp $GHOST/src/constraints/targetSelectionConstraint.cpp $GHOST/src/objectives/targetSelectionObjective.cpp -o bin/experiments_target

# debug mode with trace 
#g++ -g -std=c++11 $OPT experiments/main_target.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/unit.cpp $GHOST/src/misc/unitMap.cpp $GHOST/src/domains/targetSelectionDomain.cpp $GHOST/src/constraints/targetSelectionConstraint.cpp $GHOST/src/objectives/targetSelectionObjective.cpp -o bin/experiments_target

# release mode with trace
g++ -std=c++11 $OPT experiments/main_target.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/unit.cpp $GHOST/src/misc/unitMap.cpp $GHOST/src/domains/targetSelectionDomain.cpp $GHOST/src/constraints/targetSelectionConstraint.cpp $GHOST/src/objectives/targetSelectionObjective.cpp -o bin/experiments_target

# release mode without trace
#g++ -std=c++11 $OPT -DNDEBUG experiments/main_target.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/unit.cpp $GHOST/src/misc/unitMap.cpp $GHOST/src/domains/targetSelectionDomain.cpp $GHOST/src/constraints/targetSelectionConstraint.cpp $GHOST/src/objectives/targetSelectionObjective.cpp -o bin/experiments_target


