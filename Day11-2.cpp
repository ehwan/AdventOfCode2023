#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::ifstream input_file( "../inputs/Day11.txt" );

  std::vector<std::string> board;
  std::string line;
  while( std::getline(input_file,line) )
  {
    board.push_back( std::move(line) );
  }

  std::vector<bool> row_dotted;
  std::vector<bool> col_dotted;

  // double dotted line
  for( int j=0; j<board[0].size(); ++j )
  {
    bool all_dot = true;
    for( int i=0; i<board.size(); ++i )
    {
      if( board[i][j] != '.' )
      {
        all_dot = false;
        break;
      }
    }
    col_dotted.push_back( all_dot );
  }
  for( int i=0; i<board.size(); ++i )
  {
    bool all_dot = true;
    for( int j=0; j<board[0].size(); ++j )
    {
      if( board[i][j] != '.' )
      {
        all_dot = false;
        break;
      }
    }
    row_dotted.push_back( all_dot );
  }

  std::vector< std::pair<int,int> > galaxies;
  for( int i=0; i<board.size(); ++i )
  {
    for( int j=0; j<board[0].size(); ++j )
    {
      if( board[i][j] != '.' )
      {
        galaxies.emplace_back( i, j );
        std::cout << i << ", " << j << "\n";
      }
    }
  }

  long long answer = 0;
  for( int i=0; i<galaxies.size(); ++i )
  {
    for( int j=i+1; j<galaxies.size(); ++j )
    {
      long long length = 0;

      // rows
      int rbegin = std::min( galaxies[i].first,galaxies[j].first );
      int rend = std::max( galaxies[i].first, galaxies[j].first );
      for( int k=rbegin+1; k<=rend; ++k )
      {
        if( row_dotted[k] )
        {
          length += 1000000;
        }else {
          ++length;
        }
      }

      // cols
      int cbegin = std::min( galaxies[i].second,galaxies[j].second );
      int cend = std::max( galaxies[i].second, galaxies[j].second );
      for( int k=cbegin+1; k<=cend; ++k )
      {
        if( col_dotted[k] )
        {
          length += 1000000;
        }else {
          ++length;
        }
      }

      answer += length;
    }
  }

  std::cout << answer << "\n";

  return 0;
}