#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>

int main()
{
  /*
  std::string str =
"2413432311323\n"
"3215453535623\n"
"3255245654254\n"
"3446585845452\n"
"4546657867536\n"
"1438598798454\n"
"4457876987766\n"
"3637877979653\n"
"4654967986887\n"
"4564679986453\n"
"1224686865563\n"
"2546548887735\n"
"4322674655533";
  std::istringstream input_file( str );
  */

  std::ifstream input_file( "../inputs/Day17.txt" );

  std::string line;
  std::vector< std::vector<int> > heat_loss;
  while( std::getline(input_file,line) )
  {
    heat_loss.emplace_back();
    for( char ch : line )
    {
      heat_loss.back().push_back( ch-'0' );
    }
  }

  struct heat_loss_info_t
  {
    std::array<int,2> loss = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() };
  };
  std::vector< std::vector<heat_loss_info_t> > minimum_heat_loss;
  minimum_heat_loss.resize( heat_loss.size() );
  for( auto &i : minimum_heat_loss )
  {
    i.resize( heat_loss[0].size() );
  }

  struct bfs_info_t
  {
    int i, j;
    // 0 : from i-dir
    // 1 : from j-dir
    int from_dir;
  };
  minimum_heat_loss[0][0].loss = std::array<int,2>{ {0,0} };
  //minimum_heat_loss[0][0].loss = std::array<int,2>{ {heat_loss[0][0], heat_loss[0][0]} };
  std::vector< bfs_info_t > bfs, pong;
  bfs.push_back( {0,0,0} );
  bfs.push_back( {0,0,1} );

  while( bfs.empty() == false )
  {
    pong.clear();

    for( auto b : bfs )
    {
      int di = b.from_dir==1 ? 1 : 0;
      int dj = b.from_dir==0 ? 1 : 0;
      int new_dir = 1-b.from_dir;

      for( int sign : {-1,1} )
      {
        for( int k=4; k<=10; ++k )
        {
          int newi = b.i + di*sign*k;
          int newj = b.j + dj*sign*k;

          // out-of-range check
          if( newi<0 || newi>=heat_loss.size() || newj<0 || newj>=heat_loss[0].size() )
          {
            continue;
          }

          // heat-loss calculate
          int new_loss = minimum_heat_loss[b.i][b.j].loss[b.from_dir];
          for( int j=1; j<=k; ++j )
          {
            new_loss += heat_loss[b.i+sign*j*di][b.j+sign*j*dj];
          }
          //int new_loss = minimum_heat_loss[b.i][b.j].loss[b.from_dir] + heat_loss[newi][newj];
          if( new_loss >= minimum_heat_loss[newi][newj].loss[new_dir] )
          {
            continue;
          }

          minimum_heat_loss[newi][newj].loss[new_dir] = new_loss;
          pong.push_back( {newi,newj,new_dir} );
        }
      }
    }

    std::swap( bfs, pong );
  }

  std::cout << std::min(
      minimum_heat_loss.back().back().loss[0],
      minimum_heat_loss.back().back().loss[1]
      ) << "\n";
}
