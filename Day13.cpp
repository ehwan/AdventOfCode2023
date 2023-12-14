#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<std::string> transpose( std::vector<std::string> const& board )
{
  std::vector<std::string> ret( board[0].size() );
  for( int i=0; i<ret.size(); ++i )
  {
    ret[i].resize( board.size() );
    for( int j=0; j<board.size(); ++j )
    {
      ret[i][j] = board[j][i];
    }
  }
  return ret;
}
int search_row_reflect( std::vector<std::string> const& board )
{
  // row-reflection check
  for( int i=0; i<board.size()-1; ++i )
  {
    if( board[i] == board[i+1] )
    {
      int i0 = i;
      bool find = true;
      int j = i+1;
      while( i>=0 && j<board.size() )
      {
        if( board[i] != board[j] ){ find=false; break; }
        --i;
        ++j;
      }
      if( find )
      {
        return i0;
      }
      i = i0;
    }
  }
  return -1;
}

std::pair<int,int> solve( std::vector<std::string> const& board )
{
  int row = search_row_reflect(board);
  if( row != -1 ){ return {0,row}; }

  auto tr = transpose(board);
  return {search_row_reflect(board),0};
}
int main()
{
  std::ifstream input_file( "../inputs/Day13.txt" );

  std::string line;
  std::vector<std::string> board;
  int answer = 0;
  int col_reflect = 0;
  int row_reflect = 0;
  while( std::getline(input_file,line) )
  {
    if( line.size() == 0 )
    {
      for( auto &s : board )
      {
        std::cout << s << "\n";
      }
      int row = search_row_reflect(board);
      if( row != -1 )
      {
        row_reflect += row+1;
        std::cout << row << "\n";
      }else {
        auto tr = transpose(board);
        int col = search_row_reflect(tr);
        if( col == -1 ){ std::cout << "what?\n"; }
        col_reflect += col+1;
        std::cout << col << "\n";
      }

      board.clear();
      continue;
    }

    board.push_back( std::move(line) );
  }

  std::cout << row_reflect*100 + col_reflect << "\n";
}