#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


int dir2index( int di, int dj )
{
  if( di == 1 ){ return 0; }
  if( di == -1 ){ return 1; }
  if( dj == 1 ){ return 2; }
  if( dj == -1 ){ return 3; }
  return -1;
}
std::pair<int,int> index2dir( int i )
{
  if( i == 0 ){ return {1,0}; }
  if( i == 1 ){ return {-1,0}; }
  if( i == 2 ){ return {0,1}; }
  if( i == 3 ){ return {0,-1}; }
  return {};
}

void bfs( 
  std::vector<std::string> const& board, 
  std::vector<std::vector<std::bitset<8>>> &status,
  int i, int j,
  int di, int dj
)
{
  struct status_t
  {
    int i, j;
    int di, dj;
  };
  std::vector<status_t> bfs, pong;

  bfs.push_back( {i,j,di,dj} );
  while( bfs.empty() == false )
  {
    pong.clear();

    for( auto b : bfs )
    {
      if( b.i<0 || b.j<0 || b.i>=board.size() || b.j>=board[0].size() ){ continue; }
      int dir_index = dir2index( b.di, b.dj );
      if( status[b.i][b.j][ dir_index ] ){ continue; }
      status[b.i][b.j][dir_index] = true;

      status_t right = { b.i, b.j+1, 0, 1 };
      status_t left = { b.i, b.j-1, 0, -1 };
      status_t up = { b.i-1, b.j, -1, 0 };
      status_t down = { b.i+1, b.j, 1, 0 };
      status_t forward = { b.i+b.di, b.j+b.dj, b.di, b.dj };

      char ch = board[b.i][b.j];
      if( ch == '.' )
      {
        pong.push_back( forward );
      }else if( ch == '|' )
      {
        if( b.dj != 0 )
        {
          // split
          pong.push_back( up );
          pong.push_back( down );
        }else
        {
          // non-split
          pong.push_back( forward );
        }
      }else if( ch == '-' )
      {
        if( b.di != 0 )
        {
          // split
          pong.push_back( left );
          pong.push_back( right );
        }else
        {
          // non-split
          pong.push_back( forward );
        }
      }else if( ch == '\\' )
      {
        if( b.dj == 1 )
        {
          // right-in, down out
          pong.push_back( down );
        }else if( b.dj == -1 )
        {
          // left-in, up out
          pong.push_back( up );
        }else if( b.di == 1 )
        {
          // down in, right out
          pong.push_back( right );
        }else if( b.di == -1 )
        {
          // up in, left out
          pong.push_back( left );
        }
      }else if( ch == '/' )
      {
        if( b.dj == 1 )
        {
          // right-in, up out
          pong.push_back( up );
        }else if( b.dj == -1 )
        {
          // left-in, down out
          pong.push_back( down );
        }else if( b.di == 1 )
        {
          // down in, left out
          pong.push_back( left );
        }else if( b.di == -1 )
        {
          // up in, right out
          pong.push_back( right );
        }
      }
    }

    std::swap( bfs, pong );
  }
}
int main()
{
  /*
  std::string str =
".|...\\....\n"
"|.-.\\.....\n"
".....|-...\n"
"........|.\n"
"..........\n"
".........\\\n"
"..../.\\\\..\n"
".-.-/..|..\n"
".|....-|.\\\n"
"..//.|....";
  std::istringstream input_file( str );
  */

  std::ifstream input_file( "../inputs/Day16.txt" );

  std::vector<std::string> board;
  std::vector<std::vector<std::bitset<8>>> status;
  std::string line;
  while( std::getline(input_file,line) )
  {
    status.emplace_back();
    status.back().resize( line.size(), 0 );
    std::cout << line << "\n";
    board.push_back( std::move(line) );

  }

  bfs( board, status, 0, 0, 0, 1 );

  int answer = 0;
  for( auto &l : status )
  {
    for( auto x : l )
    {
      std::cout << x.count();
      if( x.any() ){ answer++; }
    }
    std::cout << "\n";
  }
  std::cout << answer << "\n";
}
