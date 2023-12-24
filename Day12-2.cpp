#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string duplicate_string( std::string const& str )
{
  std::string ret;
  for( int i=0; i<5; ++i )
  {
    if( i > 0 )
    {
      ret += "?";
    }
    ret += str;
  }
  return ret;
}
std::vector<int> duplicate_numbers( std::vector<int> const& numbers )
{
  std::vector<int> ret;
  ret.reserve( numbers.size()*5 );
  for( int i=0; i<5; ++i )
  {
    ret.insert( ret.end(), numbers.begin(), numbers.end() );
  }
  return ret;
}

using int_type = long long;

int_type solve( std::string const& pattern, std::vector<int> const& numbers )
{
  // [i][j]
  // using 0 ~ i blocks;
  // i'th block end at j
  std::vector<std::vector<int_type>> dp( 
      numbers.size(),
      std::vector<int_type>( pattern.size(), 0 )
  );

  // i = 0
  {
    int w = numbers[0];
    for( int j=w-1; j<pattern.size(); ++j )
    {
      // 0'th block in range [j-w+1,j]
      int start = j-w+1;

      bool possible = true;
      for( int k=0; k<start; ++k )
      {
        if( pattern[k] == '#' ){ possible = false; break; }
      }
      for( int k=start; k<=j; ++k )
      {
        if( pattern[k] == '.' ){ possible = false; break; }
      }
      if( possible )
      {
        dp[0][j] = 1;
      }
    }
  }

  for( int i=1; i<numbers.size(); ++i )
  {
    int w = numbers[i];
    for( int j=w-1; j<pattern.size(); ++j )
    {
      // i'th block in range [j-w+1,j]
      int start = j-w+1;

      bool possible = true;
      for( int k=start; k<=j; ++k )
      {
        if( pattern[k] == '.' ){ possible = false; break; }
      }

      if( possible == false )
      {
        dp[i][j] = 0;
        continue;
      }

      int_type count = 0;
      // i-1'th block's endpoint
      for( int e=start-2; e>=0; --e )
      {
        // check if pattern is '#' between e and start
        possible = true;
        for( int k=e+1; k<start; ++k )
        {
          if( pattern[k] == '#' ){ possible = false; break; }
        }

        if( possible == false )
        {
          break;
        }

        count += dp[i-1][e];
      }

      dp[i][j] = count;
    }
  }

  for( int j=pattern.size()-1; j>=0; --j )
  {
    bool possible = true;
    for( int k=j+1; k<pattern.size(); ++k )
    {
      if( pattern[k] == '#' ){ possible = false; break; }
    }

    if( possible == false )
    {
      dp.back()[j] = 0;
    }
  }
  int_type answer = 0;
  for( int j=pattern.size()-1; j>=0; --j )
  {
    answer += dp.back()[j];
  }

  return answer;
}
int main()
{
  std::ifstream input_file( "../inputs/Day12.txt" );

  std::string line;
  int_type answer = 0;
  while( std::getline(input_file,line) )
  {
    std::istringstream line_stream( std::move(line) );
    std::string spring_single;
    line_stream >> spring_single;

    std::string spring;

    std::vector<int> numbers;
    int int_;
    while( 1 )
    {
      line_stream >> int_;
      if( line_stream.fail() ){ break; }
      line_stream.seekg( 1, line_stream.cur );
      numbers.push_back( int_ );
    }
    std::vector<int> numbers_single = numbers;

    spring = duplicate_string( spring_single );
    numbers = duplicate_numbers( numbers_single );
    //spring = spring_single;
    //numbers = numbers_single;

    std::cout << spring << "\n";
    for( int n : numbers )
    {
      std::cout << n << ", ";
    }
    std::cout << "\n";

    answer += solve( spring, numbers );
  }

  std::cout << answer << "\n";

  return 0;
}
