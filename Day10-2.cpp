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

const std::pair<int,int> dps[] =
{
  {-1,0},
  {1,0},
  {0,-1},
  {0,1}
};

void dfs_segment( std::vector<std::vector<int>> &board, int i, int j, int set )
{
  if( board[i][j] ){ return; }
  board[i][j] = set;
  for( auto dp : dps )
  {
    int newi = i + dp.first;
    int newj = j + dp.second;
    if( newi<0 || newi>=board.size() || newj<0 || newj>=board[0].size() ){ continue; }

    if( board[newi][newj] ){ continue; }
    dfs_segment( board, newi, newj, set );
  }
}

int main()
{
  std::ifstream input_file( "../inputs/Day10.txt" );

  std::vector<std::string> board;
  {
    std::string line;
    while( input_file >> line )
    {
      board.push_back( std::move(line) );
    }
  }

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

  // assume 'S' ---------------------------------
  std::vector< std::pair<int,int> > S_connected_adj;
  for( auto dp : tile_map.at( 'S' ) )
  {
    std::pair<int,int> opposite = { -dp.first, -dp.second };

    int newi = Si + dp.first;
    int newj = Sj + dp.second;
    if( newi<0 || newi>=board.size() || newj<0 || newj>=board[0].size() ){ continue; }
    auto &adj_dp = tile_map.at( board[newi][newj] );

    if( std::find(adj_dp.begin(), adj_dp.end(), opposite) != adj_dp.end() )
    {
      S_connected_adj.push_back( dp );
    }
  }
  for( auto &tile : tile_map )
  {
    bool find = true;
    for( auto S_adj : S_connected_adj )
    {
      if( std::find(tile.second.begin(),tile.second.end(),S_adj) == tile.second.end() )
      {
        find = false;
        break;
      }
    }
    if( find )
    {
      board[Si][Sj] = tile.first;
      break;
    }
  }
  std::cout << "'S' is " << board[Si][Sj] << "\n";
  // -------------------------------------------

  // remove every dummy-fence -----------------------------
  std::vector< std::pair<int,int> > bfs = { {Si,Sj} };
  decltype(bfs) pong;

  // set valid fence in cycle to negative value
  board[Si][Sj] = -board[Si][Sj];
  while( bfs.empty() == false )
  {
    pong.clear();
    for( auto p : bfs )
    {
      for( auto dp : tile_map.at(-board[p.first][p.second]) )
      {
        int newi = p.first + dp.first;
        int newj = p.second + dp.second;
        if( newi<0 || newi>=board.size() || newj<0 || newj>=board[0].size() ){ continue; }
        if( board[newi][newj] < 0 ){ continue; }

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

        board[newi][newj] = -board[newi][newj];
        pong.push_back( {newi,newj} );
      }
    }
    std::swap( bfs, pong );
  }
  // remove every positive fence to '.'
  for( auto &l : board )
  {
    for( auto &x : l )
    {
      if( x < 0 ){ x = -x; }
      else{ x = '.'; }
    }
  }
  // ----------------------------------------------------------


  // build segment board
  /*
  Ex)
           . X .
    | -->  . X .
           . X .
    
           . X .
    L -->  . X X
           . . .
  */
  std::vector< std::vector<int> > segment_board;
  segment_board.resize(
    board.size()*2+1,
    std::vector<int>( board[0].size()*2 + 1, 0 )
  );

  for( int i=0; i<board.size(); ++i )
  {
    for( int j=0; j<board[0].size(); ++j )
    {
      int center_i = 2*i + 1;
      int center_j = 2*j + 1;

      for( auto dp : tile_map.at( board[i][j] ) )
      {
        segment_board[center_i][center_j] = 1;
        segment_board[center_i+dp.first][center_j+dp.second] = 1;
      }
    }
  }

  // dfs traversal for every node touching boundary ( i=0 || j=0 || i=MaxI || j=MaxJ )
  // set every visited node's value to 2
  for( int i=0; i<segment_board.size(); ++i )
  {
    if( segment_board[i][0] == 0 ){ dfs_segment(segment_board,i,0,2); }
    if( segment_board[i][segment_board[0].size()-1] == 0 ){ dfs_segment(segment_board,i,segment_board[0].size()-1,2); }
  }
  for( int j=0; j<segment_board[0].size(); ++j )
  {
    if( segment_board[0][j] == 0 ){ dfs_segment(segment_board, 0, j, 2 ); }
    if( segment_board[segment_board.size()-1][j] == 0 ){ dfs_segment(segment_board, segment_board.size()-1, j, 2 ); }
  }

  int answer = 0;
  // for every centered node ( i = 2*n+1, n \in Z )
  // value 0 means it is inside cycle ( never visited by dfs traversal )
  for( int i=1; i<segment_board.size(); i+=2 )
  {
    for( int j=1; j<segment_board[0].size(); j+=2 )
    {
      if( segment_board[i][j] == 0 ){ ++answer; }
    }
  }

  for( auto &l : segment_board )
  {
    for( auto &x : l )
    {
      std::cout << x;
    }
    std::cout << "\n";
  }
  std::cout << answer << "\n";
}