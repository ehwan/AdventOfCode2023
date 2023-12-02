#include <fstream>
#include <string>
#include <iostream>

int get_digit( char ch )
{
  if( '0'<=ch && ch<='9' ){ return (int)(ch-'0'); }
  return -1;
}
int parse( std::string const& str )
{
  int left = 0;
  for( int i=0; i<str.size(); ++i )
  {
    if( (left=get_digit(str[i])) != -1 ){ break; }
  }
  int right = 0;
  for( int i=str.size()-1; i>=0; --i )
  {
    if( (right=get_digit(str[i])) != -1 ){ break; }
  }

  return left*10 + right;
}

int main()
{
  std::ifstream input_file( "../inputs/Day1.txt" );
  std::string line;

  int answer = 0;
  while( std::getline(input_file,line) )
  {
    answer += parse(line);
  }

  std::cout << answer << "\n";

  return 0;
}