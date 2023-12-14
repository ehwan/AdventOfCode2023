#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

bool inc( std::vector<int> &gaps, int max_gap, int i )
{
  gaps[i]++;
  int sum = 0;
  for( auto g : gaps ){ sum += g; }
  if( sum > max_gap )
  {
    if( i == 0 ){ return false; }
    gaps[i] = 1;
    return inc( gaps, max_gap, i-1 );
  }
  return true;
}
bool match( std::string const& input, std::string const& pattern )
{
  for( int i=0; i<input.size(); ++i )
  {
    if( input[i] == '?' ){ continue; }

    if( input[i] != pattern[i] ){ return false; }
  }
  return true;
}
int main()
{
  std::ifstream input_file( "../inputs/Day12.txt" );

  std::string line;
  int answer = 0;
  while( std::getline(input_file,line) )
  {
    std::istringstream line_stream( std::move(line) );
    std::string spring;
    line_stream >> spring;

    std::vector<int> numbers;
    int int_;
    while( 1 )
    {
      line_stream >> int_;
      if( line_stream.fail() ){ break; }
      line_stream.seekg( 1, line_stream.cur );
      numbers.push_back( int_ );
    }

    // search every possible combination of '#'s
    std::vector<std::string> possible;

    int width = spring.size();
    int max_gaps = width;
    for( int n : numbers )
    {
      max_gaps -= n;
    }
    std::vector<int> gaps( numbers.size(), 1 );
    gaps.front() = 0;
    while( 1 )
    {
      std::string s;
      for( int i=0; i<numbers.size(); ++i )
      {
        for( int j=0; j<gaps[i]; ++j )
        {
          s.push_back( '.' );
        }
        for( int j=0; j<numbers[i]; ++j )
        {
          s.push_back( '#' );
        }
      }
      while( s.size() < width )
      {
        s.push_back( '.' );
      }
      possible.push_back( s );

      // next possible
      if( inc(gaps,max_gaps,gaps.size()-1) == false )
      {
        break;
      }
    }

    possible.erase(
      std::remove_if( possible.begin(), possible.end(),
        [&]( std::string const& pattern )
        {
          return match(spring,pattern) == false;
        } ),
        possible.end()
    );

    for( auto &s : possible )
    {
      std::cout << s << "\n";
    }

    answer += possible.size();
  }

  std::cout << answer << "\n";

  return 0;
}