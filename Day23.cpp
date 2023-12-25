#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

const std::map<char,std::pair<int,int>> slopes =
{
  { '<', {0,-1} },
  { '>', {0, 1} },
  { '^', {-1,0} },
  { 'v', {1,0} },
  { '#', {0,0} },
  { '.', {0,0} }
};
const std::pair<int,int> dps[] =
{
  {0,1},
  {0,-1},
  {1,0},
  {-1,0}
};

int dfs( std::vector<std::string> const& board, std::vector<std::vector<bool>> &visited, int i, int j )
{
  int ret;
  int newi, newj;
  
  ret = 0;
  if( board[i][j] != '.' )
  {
    auto dp = slopes.at( board[i][j] );
    newi = i + dp.first;
    newj = j + dp.second;
    if( visited[newi][newj] )
    {
      return 0;
    }
    visited[newi][newj] = true;
    ret = 1 + dfs(board,visited, newi, newj );
    visited[newi][newj] = false;
  }else
  {
    for( auto dp : dps )
    {
      int newi = i + dp.first;
      int newj = j + dp.second;
      if( newi<0 || newi>=board.size() || newj<0 || newj>=board[0].size() )
      {
        continue;
      }
      if( visited[newi][newj] )
      {
        continue;
      }
      visited[newi][newj] = true;

      ret = std::max( ret,
          1 + dfs(board,visited,newi,newj)
      );
      
      visited[newi][newj] = false;
    }
  }

  return ret;
}

int main()
{
  /*
  std::string str =
"#.#####################\n"
"#.......#########...###\n"
"#######.#########.#.###\n"
"###.....#.>.>.###.#.###\n"
"###v#####.#v#.###.#.###\n"
"###.>...#.#.#.....#...#\n"
"###v###.#.#.#########.#\n"
"###...#.#.#.......#...#\n"
"#####.#.#.#######.#.###\n"
"#.....#.#.#.......#...#\n"
"#.#####.#.#.#########v#\n"
"#.#...#...#...###...>.#\n"
"#.#.#v#######v###.###v#\n"
"#...#.>.#...>.>.#.###.#\n"
"#####v#.#.###v#.#.###.#\n"
"#.....#...#...#.#.#...#\n"
"#.#########.###.#.#.###\n"
"#...###...#...#...#.###\n"
"###.###.#.###v#####v###\n"
"#...#...#.#.>.>.#.>.###\n"
"#.###.###.#.###.#.#v###\n"
"#.....###...###...#...#\n"
"#####################.#";
  std::istringstream input_file( str );
  */
  std::ifstream input_file( "../inputs/Day23.txt" );


  std::string line;
  std::vector<std::string> board;
  while( std::getline(input_file,line) )
  {
    std::cout << line << "\n";
    board.push_back( std::move(line) );
  }


  int starti, startj;

  for( int i=0; i<board[0].size(); ++i )
  {
    if( board[0][i] == '.' )
    {
      starti = 0;
      startj = i;
      break;
    }
  }

  std::vector< std::vector<bool> > visited(
      board.size(), 
      std::vector<bool>(board[0].size(),false)
  );
  visited[starti][startj] = true;

  std::cout << dfs(board, visited, starti, startj ) << "\n";

}
