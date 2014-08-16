#!/bin/bash
GHOST=/home/flo/ghost

# g++ -std=c++11 -Ofast experiments/main_bo.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/action.cpp $GHOST/src/misc/actionMap.cpp $GHOST/src/domains/buildorderDomain.cpp $GHOST/src/constraints/buildorderConstraint.cpp  $GHOST/src/objectives/buildorderObjective.cpp -o bin/experiments_bo

g++ -std=c++11 -Ofast -DNDEBUG experiments/main_bo.cpp $GHOST/src/variables/variable.cpp $GHOST/src/variables/action.cpp $GHOST/src/misc/actionMap.cpp $GHOST/src/domains/buildorderDomain.cpp $GHOST/src/constraints/buildorderConstraint.cpp  $GHOST/src/objectives/buildorderObjective.cpp -o bin/experiments_bo

