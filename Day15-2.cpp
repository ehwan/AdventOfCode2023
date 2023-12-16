#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

int hash( std::string const& str )
{
  int answer = 0;
  for( int ch : str )
  {
    answer += ch;
    answer *= 17;
    answer %= 256;
  }
  return answer;
}

struct box_t
{
  struct lens_value_t
  {
    int uid = -1;
    int value;
  };
  int uid = 0;
  std::map< std::string, lens_value_t > lens;

  void insert( std::string const& name, int value )
  {
    auto &l = lens[name];
    if( l.uid == -1 )
    {
      l.uid = uid++;
    }
    l.value = value;
    std::cout << "insert " << name << " : " << value << "\n";
  }
  void erase( std::string const &name )
  {
    lens.erase( name );
    std::cout << "erase " << name << "\n";
  }

  std::vector<int> get_values_in_order() const
  {
    std::vector< std::pair<int,int> > uid_value_pairs;
    uid_value_pairs.reserve( lens.size() );
    for( auto &l : lens )
    {
      uid_value_pairs.emplace_back( l.second.uid, l.second.value );
    }

    std::sort( uid_value_pairs.begin(), uid_value_pairs.end() );

    std::vector<int> ret;
    ret.reserve( uid_value_pairs.size() );
    for( auto u : uid_value_pairs )
    {
      ret.push_back( u.second );
    }
    return ret;
  }
};

int main()
{
  /*
  std::string str =
  "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7";
  std::istringstream input_file( str );
  */

  std::ifstream input_file( "../inputs/Day15.txt" );

  std::string token;

  box_t boxes[256];
  while( std::getline(input_file,token,',') )
  {
    auto dash = token.find( '-' );
    auto equal = token.find( '=' );

    if( dash != token.npos )
    {
      std::string name = token.substr( 0, dash );
      int h = hash(name);
      boxes[h].erase( name );
    }else {
      std::string name = token.substr( 0, equal );
      int h = hash(name);

      boxes[h].insert( name, std::atoi(token.data()+(equal+1)) );
    }
  }

  int answer = 0;
  for( int bid=0; bid<256; ++bid )
  {
    auto values = boxes[bid].get_values_in_order();
    for( int i=0; i<values.size(); ++i )
    {
      answer += (bid+1) * (i+1) * values[i];
    }
  }

  std::cout << answer << "\n";
}