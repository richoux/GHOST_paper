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
    sat = stoi(argv[2]);
  if( argc > 2 )
    opt = stoi(argv[3]);

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
    solver.solve( sat, opt );

    if( none_of( begin(vec), end(vec), [](Unit &u){return !u.isDead() && u.canShoot() && u.getValue() != -1;} ) 
	&&
	none_of( begin(enemies), end(enemies), [](UnitEnemy &u){return !u.isDead() && u.canShoot();} ) )
    {
      for_each( begin(vec), end(vec), [](Unit &u){u.oneStep();} );
      for_each( begin(enemies), end(enemies), [](UnitEnemy &u){u.oneStep();} );
      continue;
    }

    totalDamages = 0.;
    totalDamagesEnemy = 0.;

    cout << "Tour " << tour++ << endl;

    // My units attack
    cout << ":::: My turn ::::" << endl;

    for( int i = 0 ; i < enemies.size() ; ++i )
      copyEnemies[i].data.hp = enemies[i].data.hp;
    
    for( auto &v : vec )
      if( !v.isDead() )
	if( v.canShoot() && v.getValue() != -1 )
	  totalDamages += v.doDamage( copyEnemies );
	else
	{
	  cout << v.getFullName() << ":" << v.getId() << " HP=" << v.getHP() << ", wait=" << v.canShootIn() << endl;
	  if( !v.canShoot() )
	    v.oneStep();
	}
    
    // The enemy attacks
    cout << "@@@@ Enemy's turn @@@@" << endl;

    for( int i = 0 ; i < enemies.size() ; ++i )
    {
      if( !enemies[i].isDead() )
      {
	if( enemies[i].canShoot() )
	{
	  inRange.clear();
	  for( int j = 0 ; j < vec.size() ; ++j )
	    if( enemies[i].isInRangeAndAlive( vec[j] ) )
	      inRange.push_back( j );

	  if( !inRange.empty() )
	    totalDamagesEnemy += enemies[i].doDamageAgainst( inRange[ random.getRandNum( inRange.size() ) ], vec, i );
	  else
	    cout << enemies[i].data.name << "@" << i << " HP=" << enemies[i].data.hp << ", wait=" << enemies[i].data.canShootIn << endl;	    
	}
	else
	{
	  cout << enemies[i].data.name << "@" << i << " HP=" << enemies[i].data.hp << ", wait=" << enemies[i].data.canShootIn << endl;
	  if( !enemies[i].canShoot() )
	    enemies[i].oneStep();
	}
      }
    }

    for( int i = 0 ; i < enemies.size() ; ++i )
      enemies[i].data.hp = copyEnemies[i].data.hp;
    
    deadUnits = count_if( begin(vec), end(vec), [](Unit &u){ return u.isDead(); } );
    deadEnemy = count_if( begin(enemies), end(enemies), [](UnitEnemy &u){ return u.isDead(); } );
    cout << "XXXX Turns over XXXX" << endl
	 << "Total damages from you: " << totalDamages << endl 
	 << "Total damages from the enemy: " << totalDamagesEnemy << endl
	 << "Number of dead units: " << deadUnits << endl 
	 << "Number of dead enemies: " << deadEnemy << endl;

  } while( deadUnits < numUnits && deadEnemy < numEnemy );

  if( count_if( begin(enemies), end(enemies), [&](UnitEnemy &u){ return u.isDead(); } ) == numEnemy
      &&
      count_if( begin(vec), end(vec), [&](Unit &u){ return u.isDead(); } ) < numUnits)
  {
    cout << "Winner: You!" << endl;
    for( const auto &v : vec )
      cout << v.getFullName() << ":" << v.getId() << " " << v.getHP() << " HP left" << endl;
  }
  else if( count_if( begin(enemies), end(enemies), [&](UnitEnemy &u){ return u.isDead(); } ) < numEnemy
	   &&
	   count_if( begin(vec), end(vec), [&](Unit &u){ return u.isDead(); } ) == numUnits)
  {
    cout << "Winner: The enemy..." << endl;
    for( int i = 0 ; i < enemies.size() ; ++i )
      cout << enemies[i].data.name << "@" << i << " " << enemies[i].data.hp << " HP left" << endl;
  }
  else
  {
    cout << "Draw!" << endl;
  }
}
