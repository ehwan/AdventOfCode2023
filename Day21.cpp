#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

int main()
{
  /*
  std::string str =
"...........\n"
".....###.#.\n"
".###.##..#.\n"
"..#.#...#..\n"
"....#.#....\n"
".##..S####.\n"
".##..#...#.\n"
".......##..\n"
".##.#.####.\n"
".##..##.##.\n"
"...........";
  std::istringstream input_file( str );
  */
  std::ifstream input_file( "../inputs/Day21.txt" );

  // input
  std::vector< std::string > garden;
  std::string line;
  while( std::getline( input_file, line ) )
  {
    garden.push_back( std::move(line) );
  }


  // initialize board
  // board[i][j] = minimum step count to reach (i, j)
  std::vector< std::vector<int> > board;
  board.resize( garden.size() );
  for( int i=0; i<board.size(); ++i )
  {
    board[i].resize( garden[0].size(), -1 );
  }

  // find 'S'
  int Si = -1, Sj;
  for( int i=0; i<board.size(); ++i )
  {
    for( int j=0; j<board[0].size(); ++j )
    {
      if( garden[i][j] == 'S' )
      {
        Si = i;
        Sj = j;
        break;
      }
    }
    if( Si != -1 ){ break; }
  }
  garden[Si][Sj] = '.';
  board[Si][Sj] = 0;

  // bfs
  std::vector<std::pair<int,int>> bfs, pong;
  bfs.push_back( {Si,Sj} );

  const std::pair<int,int> dps[] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
  int step = 0;
  int MAX_STEPS = 64;
  while( bfs.empty()==false && step<MAX_STEPS )
  {
    pong.clear();
    ++step;
    for( auto b : bfs )
    {
      for( auto dp : dps )
      {
        int newi = b.first + dp.first;
        int newj = b.second + dp.second;
        if( newi<0 || newi>=board.size() || newj<0 || newj>=board[0].size() ){ continue; }
        if( board[newi][newj] != -1 ){ continue; }
        if( garden[newi][newj] != '.' ){ continue; }

        board[newi][newj] = step;

        pong.push_back( {newi,newj} );
      }
    }
    std::swap( pong, bfs );
  }

  int answer = 0;
  for( auto &i : board )
  {
    for( auto j : i )
    {
      if( j > MAX_STEPS ){ continue; }
      if( (MAX_STEPS-j)%2 == 0 ){ ++answer; }
    }
  }

  std::cout << answer << "\n";
}
