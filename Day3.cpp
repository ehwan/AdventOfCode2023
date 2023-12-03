#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


bool is_digit( char ch )
{
  return '0' <= ch && ch <= '9';
}
bool is_symbol( char ch )
{
  return is_digit(ch)==false && ch!='.';
}
bool is_adjacency( int line, int i, std::vector<std::string> const& lines )
{
  for( int l=line-1; l<=line+1; ++l )
  {
    if( l < 0 || l>=lines.size() ){ continue; }
    for( int j=i-1; j<=i+1; ++j )
    {
      if( j<0 || j>=lines[line].size() ){ continue; }

      if( is_symbol(lines[l][j]) ){ return true; }
    }
  }
  return false;
}
int main()
{
  std::ifstream input_file( "../inputs/Day3.txt" );


  int answer = 0;
  std::vector<std::string> lines;
  std::string line;
  while( std::getline(input_file,line) )
  {
    lines.push_back( std::move(line) );
  }

  for( int l=0; l<lines.size(); ++l )
  {
    line = lines[l];
    for( int i=0; i<line.size(); ++i )
    {
      if( is_digit(line[i]) == false ){ continue; }

      int num = 0;
      int j = i;
      bool is_adj = false;
      while( j < line.size() && is_digit(line[j]) )
      {
        num = num*10 + (line[j]-'0');

        if( is_adj == false )
        {
          if( is_adjacency(l,j,lines) )
          {
            is_adj = true;
          }
        }
        ++j;
      }

      i = j;

      if( is_adj )
      {
        answer += num;
      }
    }
  }

  std::cout << answer << "\n";
}