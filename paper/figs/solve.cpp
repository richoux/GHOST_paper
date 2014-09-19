vector< Unit > variables = { ... }
vector< UnitEnemy  > enemies  = {  ... }  //specific  to the target selection problem
TargetSelectionDomain domain( variables.size(), &enemies );
vector< shared_ptr<TargetSelectionConstraint> > vecConstraints
      { make_shared<TargetSelectionConstraint>( &vec, &domain ) };
shared_ptr<TargetSelectionObjective> objective =
      make_shared<MaxDamage>();
Solver<Unit, TargetSelectionDomain, TargetSelectionConstraint>
      solver( &vec, &domain, vecConstraints, objective );
solver.solve();

