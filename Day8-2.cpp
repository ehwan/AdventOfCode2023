#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>


int main()
{
  /*
  std::string str =
  "LR\n"
"11A = (11B, XXX)\n"
"11B = (XXX, 11Z)\n"
"11Z = (11B, XXX)\n"
"22A = (22B, XXX)\n"
"22B = (22C, 22C)\n"
"22C = (22Z, 22Z)\n"
"22Z = (22B, 22B)\n"
"XXX = (XXX, XXX)";
std::istringstream input_file( str );
*/
  // use two-pointer to find the period of each cycle started from '**A'
  std::ifstream input_file( "../inputs/Day8.txt" );

  std::string command;
  std::getline( input_file, command );

  std::string root, left, right, dummy;

  std::map<std::string,std::string> lefts, rights;
  std::vector<std::string> ends_with_A;
  while( input_file >> root )
  {
    input_file >> dummy;
    input_file >> left;
    input_file >> right;

    std::string left_( left.begin()+1, left.begin()+1+3 );
    left = std::move(left_);
    std::string right_( right.begin(), right.begin()+3 );
    right = std::move(right_);

    lefts[root] = left;
    rights[root] = right;

    if( root.back() == 'A' )
    {
      ends_with_A.push_back( root );
    }
  }

  struct node_t
  {
    std::string name;
    int command_id;
  };
  auto next_node = [&]( node_t const& n )->node_t
  {
    char ch = command[n.command_id];
    std::string next_name =
      ch == 'L' ? lefts[n.name] : rights[n.name];
    int next_id = n.command_id + 1;
    if( next_id == command.size() ){ next_id = 0; }

    return { next_name, next_id };
  };
  struct cycle_info_t
  {
    int length;
    int start;
    int cycle_length;

    long long z_index = 0;
  };
  std::vector<cycle_info_t> cycles;
  for( int k=0; k<ends_with_A.size(); ++k )
  {
    node_t front = { ends_with_A[k], 0 };
    node_t slow = front;
    node_t fast = front;

    int first = 1;
    while( 1 )
    {
      slow = next_node(slow);
      fast = next_node(fast);
      fast = next_node(fast);
      ++first;

      if( slow.name==fast.name && slow.command_id==fast.command_id )
      {
        break;
      }
    }

    int second = 0;
    slow = front;
    while( 1 )
    {
      if( slow.name==fast.name && slow.command_id==fast.command_id )
      {
        break;
      }
      slow = next_node(slow);
      fast = next_node(fast);
      ++second;
    }

    int length = first;
    int cycle_start = second;

    cycles.push_back( {length, cycle_start, length-cycle_start} );

    std::cout << cycles.back().length << ", " << cycles.back().start << ", " << cycles.back().cycle_length << "\n";

    int i = 0;
    while( i < length )
    {
      if( front.name.back() == 'Z' )
      {
        std::cout << i << " ";
        cycles.back().z_index = i;
        std::cout << front.name << "\n";
      }
      front = next_node(front);
      ++i;
    }
    std::cout << "\n";
  }

  while( 1 )
  {
    std::sort( cycles.begin(), cycles.end(),
      [&]( cycle_info_t &c1, cycle_info_t &c2 )
      {
        return c1.z_index < c2.z_index;
      } );
    
    bool find = true;
    for( int i=1; i<cycles.size(); ++i )
    {
      if( cycles[i-1].z_index != cycles[i].z_index ){ find=false; break; }
    }
    if( find )
    {
      std::cout << cycles[0].z_index << "\n";
      return 0;
    }
    cycles[0].z_index += cycles[0].cycle_length;
  }
}
