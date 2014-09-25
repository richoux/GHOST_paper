#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <string>

#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/variables/unit.hpp"
#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/domains/targetSelectionDomain.hpp"
#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/constraints/targetSelectionConstraint.hpp"
#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/objectives/targetSelectionObjective.hpp"
#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/misc/unitMap.hpp"
#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/solver.hpp"
#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/misc/random.hpp"

using namespace ghost;
using namespace std;

vector<int> getLivingEnemiesInRange( const UnitEnemy &u, const vector<Unit> &vec )
{
  vector<int> inRange;

  for( int j = 0 ; j < vec.size() ; ++j )
    if( u.isInRangeAndAlive( vec[j] ) )
      inRange.push_back( j );
      
  return inRange;
}


int main(int argc, char **argv)
{
  // input
  // vector< pair<string, int> > input;
  
  // ifstream inputFile;
  // ofstream outputFile;
  // char read[256];
  // string str;
  // int count = 0;

  // string action;
  // int time;

  int sat = 20;
  int opt = 30;
  if( argc > 1 )
    sat = stoi(argv[1]);
  if( argc > 2 )
    opt = stoi(argv[2]);

  // inputFile.open( argv[1], std::ifstream::in );
  // if( inputFile.is_open() && inputFile.peek() != std::ifstream::traits_type::eof() )
  // {
  //   while( inputFile >> read )
  //   {
  //     str = read;

  //     if( count % 3 == 0 )
  //     {
  // 	if( isdigit( str[0] ) )
  // 	{
  // 	  time = stoi(str);
  // 	  break;
  // 	}
  // 	else
  // 	  action = str;
  //     }
  //     else if( count % 3 == 1 )
  //     {
  // 	input.emplace_back( action, stoi(str) );
  //     }

  //     ++count;
  //   }
  // }
  
  // Define objective
  // nil

  // Define variables
  vector< Unit > vec {
    Unit( unitOf["Terran_Marine"], {30, 30} ),
    Unit( unitOf["Terran_Marine"], {50, 30} ),
    Unit( unitOf["Terran_Marine"], {70, 30} ),
    Unit( unitOf["Terran_Marine"], {90, 30} ),
    Unit( unitOf["Terran_Marine"], {110, 30} ),
    Unit( unitOf["Terran_Goliath"], {10, 65} ),
    Unit( unitOf["Terran_Vulture"], {50, 65} ),
    Unit( unitOf["Terran_Vulture"], {90, 65} ),
    Unit( unitOf["Terran_Goliath"], {130, 65} ),
    Unit( unitOf["Terran_Siege_Tank_Tank_Mode"], {10, 102} ),
    Unit( unitOf["Terran_Ghost"], {65, 102} ),
    Unit( unitOf["Terran_Ghost"], {75, 102} ),
    Unit( unitOf["Terran_Siege_Tank_Tank_Mode"], {130, 102} ),
    Unit( unitOf["Terran_Siege_Tank_Siege_Mode"], {70, 139} ),
  };

  // Define enemies, mirror to our units
  vector< UnitEnemy > enemies;
  for( int i = 0 ; i < vec.size() ; ++i )
    enemies.emplace_back( UnitEnemy( vec.at(i).getData(), { vec.at(i).getX(), -vec.at(i).getY() } ) );

  // Define domain
  TargetSelectionDomain domain( vec.size(), &enemies );
  
  // Define constraints
  vector< shared_ptr<TargetSelectionConstraint> > vecConstraints { make_shared<TargetSelectionConstraint>( &vec, &domain ) };

  // Define objective
  shared_ptr<TargetSelectionObjective> objective = make_shared<MaxDamage>();
  
  Solver<Unit, TargetSelectionDomain, TargetSelectionConstraint> solver( &vec, &domain, vecConstraints, objective );
  // Solver<Unit, TargetSelectionDomain, TargetSelectionConstraint> solver( &vec, &domain, vecConstraints );

  Random random;
  vector<int> inRange;

  int numUnits = vec.size();
  int numEnemy = enemies.size();
  
  int deadUnits;
  int deadEnemy;

  double totalDamages;
  double totalDamagesEnemy;

  int tour = 1;

  vector< UnitEnemy > copyEnemies( enemies );

  do
  {
    if( none_of( begin(vec), end(vec), [&](Unit &u){return !u.isDead() && u.canShoot() && !domain.getLivingEnemiesInRange( u ).empty(); } ) 
	&&
	none_of( begin(enemies), end(enemies), [&](UnitEnemy &u){return !u.isDead() && u.canShoot() && !getLivingEnemiesInRange( u, vec ).empty(); } ) )
    {
      for_each( begin(vec), end(vec), [](Unit &u){u.oneStep();} );
      for_each( begin(enemies), end(enemies), [](UnitEnemy &u){u.oneStep();} );
      continue;
    }

    solver.solve( sat, opt );

    totalDamages = 0.;
    totalDamagesEnemy = 0.;

#ifndef NDEBUG
    cout << "Tour " << tour++ << endl;

    // My units attack
    cout << ":::: My turn ::::" << endl;
#endif

    for( int i = 0 ; i < enemies.size() ; ++i )
      copyEnemies[i].data.hp = enemies[i].data.hp;
    
    for( auto &v : vec )
      if( !v.isDead() )
	if( v.canShoot() && v.getValue() != -1 )
	  totalDamages += v.doDamage( copyEnemies );
	else
	{
#ifndef NDEBUG
	  cout << v.getFullName() << ":" << v.getId() << " HP=" << v.getHP() << ", wait=" << v.canShootIn() << endl;
#endif
	  if( !v.canShoot() )
	    v.oneStep();
	}
    
#ifndef NDEBUG
    // cout << endl << endl << "Simulation" << endl;
    // for( auto &v : vec )
    // {
    //   if( !v.isDead() && v.canShootIn() == v.getCooldown() )
    //   {
    // 	int backup = v.getValue();
	
    // 	for( int j = 0 ; j < copyEnemies.size() ; ++j )
    // 	{
    // 	  v.setValue( j );
    // 	  auto hits = v.computeDamage( &copyEnemies );
    // 	  if( hits.at( j ) != 0. )
    // 	    cout << v.getFullName() << ":" << v.getId() << " can hit " << copyEnemies.at(j).data.name << "@" << j << " with " << hits.at( j ) << " (dist=" << v.distanceFrom(copyEnemies.at(j)) << ")" << endl;
    // 	}
	
    // 	v.setValue( backup );
    //   }
    // }
    // cout << endl << endl;
#endif
	


    // The enemy attacks
#ifndef NDEBUG
    cout << "@@@@ Enemy's turn @@@@" << endl;
#endif

    for( int i = 0 ; i < enemies.size() ; ++i )
    {
      if( !enemies[i].isDead() )
      {
	if( enemies[i].canShoot() )
	{
	  inRange = getLivingEnemiesInRange( enemies[i], vec );

	  if( !inRange.empty() )
	    totalDamagesEnemy += enemies[i].doDamageAgainst( inRange[ random.getRandNum( inRange.size() ) ], vec, i );
#ifndef NDEBUG
	  else
	    cout << enemies[i].data.name << "@" << i << " HP=" << enemies[i].data.hp << ", wait=" << enemies[i].data.canShootIn << endl;	    
#endif
	}
	else
	{
#ifndef NDEBUG
	  cout << enemies[i].data.name << "@" << i << " HP=" << enemies[i].data.hp << ", wait=" << enemies[i].data.canShootIn << endl;
#endif
	  if( !enemies[i].canShoot() )
	    enemies[i].oneStep();
	}
      }
    }

    for( int i = 0 ; i < enemies.size() ; ++i )
      enemies[i].data.hp = copyEnemies[i].data.hp;
    
    deadUnits = count_if( begin(vec), end(vec), [](Unit &u){ return u.isDead(); } );
    deadEnemy = count_if( begin(enemies), end(enemies), [](UnitEnemy &u){ return u.isDead(); } );
#ifndef NDEBUG
    cout << "XXXX Turns over XXXX" << endl
    	 << "Total damages from you: " << totalDamages << endl 
    	 << "Total damages from the enemy: " << totalDamagesEnemy << endl
    	 << "Number of dead units: " << deadUnits << endl 
    	 << "Number of dead enemies: " << deadEnemy << endl;
#endif

  } while( deadUnits < numUnits && deadEnemy < numEnemy );

  double total_hp = 0.;
  
  if( count_if( begin(enemies), end(enemies), [&](UnitEnemy &u){ return u.isDead(); } ) == numEnemy
      &&
      count_if( begin(vec), end(vec), [&](Unit &u){ return u.isDead(); } ) < numUnits)
  {
    for( const auto &v : vec )
      if( !v.isDead() )
	total_hp += v.getHP();
    
    cout << "Winner: You!" << endl
	 << "Diff: " << deadEnemy - deadUnits << endl
	 << "HP: " << total_hp << endl;
    
#ifndef NDEBUG
    for( const auto &v : vec )
      cout << v.getFullName() << ":" << v.getId() << " " << v.getHP() << " HP left" << endl;
#endif
  }
  else if( count_if( begin(enemies), end(enemies), [&](UnitEnemy &u){ return u.isDead(); } ) < numEnemy
	   &&
	   count_if( begin(vec), end(vec), [&](Unit &u){ return u.isDead(); } ) == numUnits)
  {
    for( const auto &e : enemies )
      if( !e.isDead() )
	total_hp += e.data.hp;

    cout << "Winner: The enemy..." << endl
      	 << "Diff: " << deadEnemy - deadUnits << endl
      	 << "HP: " << total_hp << endl;
    
#ifndef NDEBUG
    for( int i = 0 ; i < enemies.size() ; ++i )
      cout << enemies[i].data.name << "@" << i << " " << enemies[i].data.hp << " HP left" << endl;
#endif
  }
  else
  {
    cout << "Draw!" << endl;
  }
}
