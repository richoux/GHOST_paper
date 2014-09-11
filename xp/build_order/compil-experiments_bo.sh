#!/bin/bash
GHOST=/home/flo/ghost

rm ./bin/experiments_bo -f

# debug mode without trace 
#g++ -std=c++11 -g -DNDEBUG experiments/main_bo.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/action.cpp $GHOST/src/misc/actionMap.cpp $GHOST/src/domains/buildorderDomain.cpp $GHOST/src/constraints/buildorderConstraint.cpp  $GHOST/src/objectives/buildorderObjective.cpp -o bin/experiments_bo

# debug mode with trace 
#g++ -std=c++11 -g experiments/main_bo.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/action.cpp $GHOST/src/misc/actionMap.cpp $GHOST/src/domains/buildorderDomain.cpp $GHOST/src/constraints/buildorderConstraint.cpp  $GHOST/src/objectives/buildorderObjective.cpp -o bin/experiments_bo

# release mode with trace
g++ -std=c++11 -Ofast experiments/main_bo.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/action.cpp $GHOST/src/misc/actionMap.cpp $GHOST/src/domains/buildorderDomain.cpp $GHOST/src/constraints/buildorderConstraint.cpp  $GHOST/src/objectives/buildorderObjective.cpp -o bin/experiments_bo

# release mode without trace
#g++ -std=c++11 -Ofast -DNDEBUG experiments/main_bo.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/action.cpp $GHOST/src/misc/actionMap.cpp $GHOST/src/domains/buildorderDomain.cpp $GHOST/src/constraints/buildorderConstraint.cpp  $GHOST/src/objectives/buildorderObjective.cpp -o bin/experiments_bo


