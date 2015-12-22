set of int: Units = 0..13;
set of int: AllUnits = 0..27;
set of int: Range = -139..139;

array[Units] of var Units: unit

array[AllUnits] of int: damagesDone

array[AllUnits] of int: hp;
array[AllUnits] of int: armor;
array[AllUnits] of int: damage;
array[AllUnits] of float: rangeMin;
array[AllUnits] of float: rangeMax;
array[AllUnits] of int: x;
array[AllUnits] of int: y;
array[AllUnits] of int: enemyX;
array[AllUnits] of int: enemyY;

constraint forall(i in Units)
  ( inRange( i, unit[i] ) );

predicate inRange(var int: source, var int: target) =
  let {float: distance = sqrt( pow( x[target] - x[source], 2 ) + pow( y[target] - y[source], 2 ) )} in
  distance >= rangeMin[source] /\ distance <= rangeMax[source];

solve maximize sum ( i in Units )

output [show(unit), "\n"]