#include <iostream>
#include <vector>
#include <fstream>


bool is_digit( char ch )
{
  return '0' <= ch && ch <= '9';
}
int main()
{
  std::ifstream input_file( "../inputs/Day3.txt" );


  int answer = 0;
  std::vector<std::vector<int>> lines;
  std::string line;
  while( std::getline(input_file,line) )
  {
    lines.emplace_back();
    lines.back().resize( line.size() );
    for( int i=0; i<line.size(); ++i )
    {
      if( line[i] == '*' ){ lines.back()[i] = -1; continue; }
      if( is_digit(line[i]) == false ){ lines.back()[i] = -2; continue; }

      int num = 0;
      int j = i;
      while( j < line.size() && is_digit(line[j]) )
      {
        num = num*10 + (line[j]-'0');
        ++j;
      }
      for( int k=i; k<j; ++k )
      {
        lines.back()[k] = num;
      }

      i = j-1;
    }
  }

  for( int l=0; l<lines.size(); ++l )
  {
    for( int i=0; i<lines[l].size(); ++i )
    {
      if( lines[l][i] != -1 ){ continue; }

      int number_count = 0;
      int number_times = 1;

      for( int l_=l-1; l_<=l+1; ++l_ )
      {
        if( l_<0 || l_>=lines.size() ){ continue; }
        int prev_num = -1;
        for( int i_=i-1; i_<=i+1; ++i_ )
        {
          if( i_<0 || i_>=lines[l_].size() ){ continue; }

          if( lines[l_][i_] >= 0 && lines[l_][i_] != prev_num )
          {
            prev_num = lines[l_][i_];
            ++number_count;
            number_times *= lines[l_][i_];
          }
        }
      }
      if( number_count == 2 )
      {
        answer += number_times;
      }
    }
  }
  std::cout << answer << "\n";
}