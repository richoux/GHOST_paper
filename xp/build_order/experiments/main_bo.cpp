#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <string>

#include "/home/flo/ghost/include/variables/action.hpp"
#include "/home/flo/ghost/include/domains/buildorderDomain.hpp"
#include "/home/flo/ghost/include/constraints/buildorderConstraint.hpp"
#include "/home/flo/ghost/include/objectives/buildorderObjective.hpp"
#include "/home/flo/ghost/include/misc/actionMap.hpp"
#include "/home/flo/ghost/include/solver.hpp"

using namespace ghost;
using namespace std;

int main(int argc, char **argv)
{
  // Define variables
  vector< Action > vec;

  // BO list
  vector< pair<string, int> > input;
  
  ifstream inputFile;
  ofstream outputFile;
  char read[256];
  string str;
  // string delim = " ";
  // string token[2];
  // size_t pos;
  int count = 0;

  string action;
  int time;

  int opt = 1000;
  if( argc > 1 )
    opt = stoi(argv[2]);
  
  inputFile.open( argv[1], std::ifstream::in );
  if( inputFile.is_open() && inputFile.peek() != std::ifstream::traits_type::eof() )
  {
    while( inputFile >> read )
    {
      str = read;

      if( count % 3 == 0 )
      {
	if( isdigit( str[0] ) )
	{
	  time = stoi(str);
	  break;
	}
	else
	  action = str;
      }
      else if( count % 3 == 1 )
      {
	input.emplace_back( action, stoi(str) );
      }

      ++count;
      
      // while( count < 2 )
      // {
      // 	pos = str.find( delim );
      // 	if( pos == std::string::npos )
      // 	{
      // 	  time = stoi(str);
      // 	  break;
      // 	}
	
      // 	token[count] = str.substr( 0, pos );
      // 	str.erase( 0, pos + 1 );
      // 	++count;
      // }
    }
  }
  
  // Define objective
  shared_ptr<BuildOrderObjective> objective = make_shared<MakeSpanMaxProd>( input, vec );

  // Define domain
  BuildOrderDomain domain( vec.size(), &vec );
  
  // Define constraints
  vector< shared_ptr<BuildOrderConstraint> > vecConstraints { make_shared<BuildOrderConstraint>( &vec, &domain ) };

  Solver<Action, BuildOrderDomain, BuildOrderConstraint> solver(&vec, &domain, vecConstraints, objective );

  solver.solve( 30, opt );
  cout << "Time reference: " << static_cast<double>(time)/15.1 << endl;
}
