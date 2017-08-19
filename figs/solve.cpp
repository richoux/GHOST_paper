// Variables
vector< Unit > variables = { ... }

// Specific to the target selection problem
vector< UnitEnemy  > enemies  = {  ... }

// Domain  
TargetDomain domain( variables.size(), &enemies );

// Constraints
vector< shared_ptr<TargetConstraint> > constraints
{ make_shared<TargetConstraint>( &variables, &domain ) };

// Objective
shared_ptr<TargetObjective> objective = make_shared<MaxDamage>();

// Solver
Solver<Unit, TargetDomain, TargetConstraint>
  solver( &variables, &domain, constraints, objective );

// Call Solver::solve
solver.solve();




