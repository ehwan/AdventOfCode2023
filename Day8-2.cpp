#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>


unsigned long long gcd( unsigned long long a ,unsigned long long b )
{
  if( a > b ){ std::swap(a,b); }

  if( a == 0 ){ return b; }
  return gcd( b%a, a );
}
unsigned long long lcm( unsigned long long a, unsigned long long b )
{
  return (a*b)/gcd(a,b);
}

struct cycle_info_t
{
  unsigned long long cycle_length;
  unsigned long long z_index;
};

cycle_info_t combine_cycle( cycle_info_t a, cycle_info_t b )
{
  unsigned long long ai = a.z_index;
  unsigned long long bi = b.z_index;
  while( ai != bi )
  {
    //std::cout << "before : ";
    //std::cout << ai << " , " << bi << "\n";
    if( ai < bi )
    {
      auto diff = bi - ai;
      auto count = diff / a.cycle_length;
      if( diff % a.cycle_length ){ ++count; }
      ai += a.cycle_length * count;
      //std::cout << "add to A : " << a.cycle_length * count << "\n";
    }
    else
    { 
      auto diff = ai - bi;
      auto count = diff / b.cycle_length;
      if( diff % b.cycle_length ){ ++count; }
      bi += b.cycle_length * count;
      //std::cout << "add to B : " << a.cycle_length * count << "\n";
    }
    //std::cout << "after : ";
    //std::cout << ai << " , " << bi << "\n";
  }

  unsigned long long cycle_length_lcm = lcm( a.cycle_length, b.cycle_length );
  return { cycle_length_lcm, ai };
}

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

    int third = 0;
    while( 1 )
    {
      fast = next_node(fast);
      ++third;

      if( slow.name==fast.name && slow.command_id==fast.command_id )
      {
        break;
      }
    }

    int length = second + third;
    int cycle_start = second;
    int cycle_length = third;

    cycles.emplace_back();
    cycles.back().cycle_length = cycle_length;

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

    std::cout << "Length: " << length << "\n";
    std::cout << "Start: " << cycle_start << "\n";
    std::cout << "CLength: " << cycle_length << "\n";
    std::cout << "\n";
  }
  std::cout << "Cycle...\n";
  for( auto c : cycles )
  {
    std::cout << "zindex: " << c.z_index << ", ";
    std::cout << "length: " << c.cycle_length << "\n";
  }

  cycle_info_t c0 = cycles[0];
  std::cout << c0.z_index << ", " << c0.cycle_length << "\n";
  for( int i=1; i<cycles.size(); ++i )
  {
    std::cout << "combine with " << i << " ...\n";
    c0 = combine_cycle( c0, cycles[i] );
    std::cout << c0.z_index << ", " << c0.cycle_length << "\n";
  }
  std::cout << c0.z_index << "\n";
  return 0;
}
