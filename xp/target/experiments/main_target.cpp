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
#include "/home/flo/Dropbox/Recherche/Programmes/GHOST/include/objectives/objective.hpp"
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
    Unit( unitOf["Terran_Marine"], {10, 40} ),
    Unit( unitOf["Terran_Marine"], {30, 40} ),
    Unit( unitOf["Terran_Marine"], {50, 40} ),
    Unit( unitOf["Terran_Marine"], {70, 40} ),
    Unit( unitOf["Terran_Marine"], {90, 40} ),
    Unit( unitOf["Terran_Vulture"], {30, 65} ),
    Unit( unitOf["Terran_Vulture"], {70, 65} ),
    Unit( unitOf["Terran_Siege_Tank_Tank_Mode"], {50, 102} ),
  };

  // Define enemies
  vector< UnitEnemy > enemies {
    UnitEnemy( unitOf["Terran_Marine"], {10, -40} ),
      UnitEnemy( unitOf["Terran_Marine"], {30, -40} ),
      UnitEnemy( unitOf["Terran_Marine"], {50, -40} ),
      UnitEnemy( unitOf["Terran_Marine"], {70, -40} ),
      UnitEnemy( unitOf["Terran_Marine"], {90, -40} ),
      UnitEnemy( unitOf["Terran_Vulture"], {30, -65} ),
      UnitEnemy( unitOf["Terran_Vulture"], {70, -65} ),
      UnitEnemy( unitOf["Terran_Siege_Tank_Tank_Mode"], {50, -102} )
  };
    
  // Define domain
  TargetSelectionDomain domain( vec.size(), &enemies );
  
  // Define constraints
  vector< shared_ptr<TargetSelectionConstraint> > vecConstraints { make_shared<TargetSelectionConstraint>( &vec, &domain ) };

  Solver<Unit, TargetSelectionDomain, TargetSelectionConstraint> solver( &vec, &domain, vecConstraints );

  Random random;
  vector<Unit*> inRange;

  int numUnits = vec.size();
  int numEnemy = enemies.size();
  
  int deadUnits;
  int deadEnemy;

  int tour = 1;


  // 3 problems:
  // 1. my units don't take damage (object copy somewhere)
  // 2. my tank never shoot the enemy tank
  // 3. I must copy vectors in order to not have dead enemies before they shoot

  cout << numUnits << " " << numEnemy << endl;
  cout << "distance: " << vec[7].distanceFrom( enemies[7] ) << endl;
  do
  {
    cout << "Tour " << tour++ << endl;
    solver.solve( sat, opt );

    // My units attack
    for( auto &v : vec )
      if( !v.isDead() )
	if( v.canShoot() && v.getValue() != -1 )
	  v.doDamage( enemies );
	else
	  v.oneStep();

    // The enemy attacks
    for( int i = 0 ; i < enemies.size() ; ++i )
    {
      if( !enemies[i].isDead() )
      {
	auto e = enemies[i];
	if( e.canShoot() )
	{
	  inRange.clear();
	  for( auto &v : vec )
	    if( e.isInRangeAndAlive( v ) )
	      inRange.push_back( &v );
	  
	  e.doDamageAgainst( inRange[ random.getRandNum( inRange.size() ) ], vec, i );
	}
	else
	  e.oneStep();
      }
    }

    deadUnits = count_if( begin(vec), end(vec), [&](Unit &u){ return u.isDead(); } );
    deadEnemy = count_if( begin(enemies), end(enemies), [&](UnitEnemy &u){ return u.isDead(); } );
    cout << "Nber dead units: " << deadUnits << endl 
	 << "Nber dead enemies: " << deadEnemy << endl;

  } while( deadUnits < numUnits && deadEnemy < numEnemy );

  if( count_if( begin(vec), end(vec), [&](Unit &u){ return u.isDead(); } ) == numUnits )
  {
    cout << "Winner: You!" << endl;
    for( const auto &v : vec )
      cout << v.getFullName() << ":" << v.getId() << " " << v.getHP() << " HP left" << endl;
  }
  else
  {
    cout << "Winner: The enemy..." << endl;
    for( int i = 0 ; i < enemies.size() ; ++i )
      cout << enemies[i].data.name << "@" << i << " " << enemies[i].data.hp << " HP left" << endl;
  }  
}
