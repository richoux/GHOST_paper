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
    // Unit( unitOf["Terran_Firebat"], {20, 10} ),
    // Unit( unitOf["Terran_Firebat"], {40, 10} ),
    // Unit( unitOf["Terran_Firebat"], {60, 10} ),
    // Unit( unitOf["Terran_Firebat"], {80, 10} ),
    Unit( unitOf["Terran_Marine"], {10, 40} ),
    Unit( unitOf["Terran_Marine"], {30, 40} ),
    Unit( unitOf["Terran_Marine"], {50, 40} ),
    Unit( unitOf["Terran_Marine"], {70, 40} ),
    Unit( unitOf["Terran_Marine"], {90, 40} ),
    Unit( unitOf["Terran_Vulture"], {40, 65} ),
    Unit( unitOf["Terran_Vulture"], {60, 65} ),
    Unit( unitOf["Terran_Siege_Tank_Tank_Mode"], {15, 65} ),
    Unit( unitOf["Terran_Siege_Tank_Tank_Mode"], {85, 65} ),
    Unit( unitOf["Terran_Siege_Tank_Siege_Mode"], {50, 139} ),
  };

  // Define enemies, mirror to our units
  vector< UnitEnemy > enemies;
  for( int i = 0 ; i < vec.size() ; ++i )
    enemies.emplace_back( UnitEnemy( vec.at(i).getData(), { vec.at(i).getX(), -vec.at(i).getY() } ) );

  // Define domain
  TargetSelectionDomain domain( vec.size(), &enemies );
  
  // Define constraints
  vector< shared_ptr<TargetSelectionConstraint> > vecConstraints { make_shared<TargetSelectionConstraint>( &vec, &domain ) };

  Solver<Unit, TargetSelectionDomain, TargetSelectionConstraint> solver( &vec, &domain, vecConstraints );

  Random random;
  vector<int> inRange;

  int numUnits = vec.size();
  int numEnemy = enemies.size();
  
  int deadUnits;
  int deadEnemy;

  int tour = 1;

  vector< UnitEnemy > copyEnemies( enemies );

  do
  {
    cout << "Tour " << tour++ << endl;
    solver.solve( sat, opt );

    // My units attack
    cout << ":::: My turn ::::" << endl;

    for( int i = 0 ; i < enemies.size() ; ++i )
      copyEnemies[i].data.hp = enemies[i].data.hp;
    
    for( auto &v : vec )
      if( !v.isDead() )
	if( v.canShoot() && v.getValue() != -1 )
	  v.doDamage( copyEnemies );
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
	    enemies[i].doDamageAgainst( inRange[ random.getRandNum( inRange.size() ) ], vec, i );
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
