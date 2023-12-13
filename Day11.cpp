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
    if( all_dot )
    {
      for( int i=0; i<board.size(); ++i )
      {
        board[i].insert( board[i].begin()+j, '.' );
      }
      ++j;
    }
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
    if( all_dot )
    {
      std::string new_line( board[0].size(), '.' );
      board.insert( board.begin()+i, std::move(new_line) );
      ++i;
    }
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

  int answer = 0;
  for( int i=0; i<galaxies.size(); ++i )
  {
    for( int j=i+1; j<galaxies.size(); ++j )
    {
      int di = galaxies[i].first - galaxies[j].first;
      int dj = galaxies[i].second- galaxies[j].second;
      answer += std::abs(di) + std::abs(dj);
    }
  }

  std::cout << answer << "\n";

  return 0;
}