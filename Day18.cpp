#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <tuple>

const std::pair<int,int> didj[] =
{
  {1,0},
  {-1,0},
  {0,1},
  {0,-1}
};

void dfs_set( std::vector<std::vector<int>> &board, int i, int j, int set )
{
  if( board[i][j] == set ){ return; }
  board[i][j] = set;
  for( auto dp : didj )
  {
    int newi = i + dp.first;
    int newj = j + dp.second;
    if( newi<0 || newj<0 || newi>=board.size() || newj>=board[0].size() ){ continue; }
    if( board[newi][newj] == set ){ continue; }
    if( board[newi][newj] == 1 ){ continue; }
    dfs_set( board, newi, newj, set );
  }
}
int main()
{
  /*
  std::string str =
"R 6 (#70c710)\n"
"D 5 (#0dc571)\n"
"L 2 (#5713f0)\n"
"D 2 (#d2c081)\n"
"R 2 (#59c680)\n"
"D 2 (#411b91)\n"
"L 5 (#8ceee2)\n"
"U 2 (#caa173)\n"
"L 1 (#1b58a2)\n"
"U 2 (#caa171)\n"
"R 2 (#7807d2)\n"
"U 3 (#a77fa3)\n"
"L 2 (#015232)\n"
"U 2 (#7a21e3)";
  std::istringstream input_file( str );
  */
  std::ifstream input_file( "../inputs/Day18.txt" );

  std::map<char,std::pair<int,int>> dirmap =
  {
    { 'R', {0,1} },
    { 'L', {0,-1} },
    { 'U', {-1,0} },
    { 'D', {1,0} }
  };

  std::string line;
  std::vector< std::pair<int,int> > vertices;
  vertices.push_back( {0,0} );
  std::pair<int,int> min_bound = {0,0};
  std::pair<int,int> max_bound = {0,0};
  auto add_vertex = [&]( char ch, int count )
  {
    auto dir = dirmap[ ch ];
    auto p = vertices.back();
    p.first += dir.first * count;
    p.second += dir.second * count;
    vertices.push_back( p );

    min_bound.first = std::min( min_bound.first, p.first );
    min_bound.second= std::min( min_bound.second, p.second );
    max_bound.first = std::max( max_bound.first, p.first );
    max_bound.second= std::max( max_bound.second, p.second );
  };
  while( std::getline( input_file, line ) )
  {
    char dir_char;
    int count;
    std::istringstream line_stream( line );
    line_stream >> dir_char >> count;

    add_vertex( dir_char, count );
  }

  std::cout << "Bound :\n";
  std::cout << "(" << min_bound.first << ", " << min_bound.second << ")->";
  std::cout << "(" << max_bound.first << ", " << max_bound.second << ")\n";

  int M = max_bound.first - min_bound.first + 1;
  int N = max_bound.second - min_bound.second + 1;
  std::vector< std::vector<int> > board( M, std::vector<int>(N, 0) );

  for( int k=0; k<vertices.size()-1; ++k )
  {
    auto p0 = vertices[k];
    auto p1 = vertices[k+1];
    auto pp = std::min(p0,p1);
    p1 = std::max(p0,p1);
    p0 = pp;

    for( int i=p0.first; i<=p1.first; ++i )
    {
      for( int j=p0.second; j<=p1.second; ++j )
      {
        board[i-min_bound.first][j-min_bound.second] = 1;
      }
    }
  }

  for( int i=0; i<board.size(); ++i )
  {
    if( board[i][0] == 0 ){ dfs_set(board,i,0,2); }
    if( board[i][board[0].size()-1] == 0 ){ dfs_set(board,i,board[0].size()-1,2); }
  }
  for( int j=0; j<board[0].size(); ++j )
  {
    if( board[0][j] == 0 ){ dfs_set(board,0,j,2); }
    if( board[board.size()-1][j] == 0 ){ dfs_set(board,board.size()-1,j,2); }
  }

  int answer = 0;
  for( int i=0; i<board.size(); ++i )
  {
    for( int j=0; j<board[0].size(); ++j )
    {
      if( board[i][j] == 1 || board[i][j] == 0 ){ ++answer; }
    }
  }
  std::cout << answer << std::endl;
}
