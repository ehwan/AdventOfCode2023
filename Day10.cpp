#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

// i-j direction
// O ------> +j
// |
// |
// +i
const std::map<char,std::vector<std::pair<int,int>>> tile_map =
{
  { '|', { {-1,0}, {1,0} } },
  { '-', { {0,1}, {0,-1} } },
  { 'L', { {-1,0}, {0,1} } },
  { 'J', { {-1,0}, {0,-1} } },
  { '7', { {0,-1}, {1,0} } },
  { 'F', { {1,0}, {0,1} } },
  { '.', {} },
  { 'S', { {-1,0}, {1,0}, {0,-1}, {0,1} } }
};

int main()
{
  std::ifstream input_file( "../inputs/Day10.txt" );

  std::vector<std::string> board;
  std::string line;
  while( input_file >> line )
  {
    board.push_back( std::move(line) );
  }

  std::vector<std::vector<int>> distance_map( board.size(), std::vector<int>(board[0].size(),-1) );

  // find 'S'
  int Si = -1, Sj = -1;
  for( int i=0; i<board.size(); ++i )
  {
    for( int j=0; j<board[i].size(); ++j )
    {
      if( board[i][j] == 'S' )
      {
        Si = i;
        Sj = j;
        break;
      }
    }

    if( Si != -1 ){ break; }
  }

  distance_map[Si][Sj] = 0;
  std::vector< std::pair<int,int> > bfs = { {Si,Sj} };
  decltype(bfs) pong;

  std::cout << Si << ", " << Sj << ": " << 'S' << "\n";

  int answer = 0;
  while( bfs.empty() == false )
  {
    pong.clear();
    for( auto p : bfs )
    {
      for( auto dp : tile_map.at(board[p.first][p.second]) )
      {
        int newi = p.first + dp.first;
        int newj = p.second + dp.second;
        if( newi<0 || newi>=board.size() || newj<0 || newj>=board[0].size() ){ continue; }
        if( distance_map[newi][newj] != -1 ){ continue; }

        auto &adj_dp = tile_map.at( board[newi][newj] );
        if(
          std::find(
            adj_dp.begin(),
            adj_dp.end(),
            std::pair<int,int>(-dp.first,-dp.second)
          ) == adj_dp.end() 
        )
        {
          continue;
        }

        std::cout << newi << ", " << newj << ": " << board[newi][newj] << "\n";

        distance_map[newi][newj] = distance_map[p.first][p.second] + 1;
        pong.push_back( {newi,newj} );

        answer = std::max( answer, distance_map[newi][newj] );
      }
    }

    std::swap( bfs, pong );
  }

  std::cout << answer << "\n";
}