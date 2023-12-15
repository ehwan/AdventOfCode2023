#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>

int calculate_load( std::vector<std::string> const& board )
{
  int answer = 0;
  for( int i=0; i<board.size(); ++i )
  {
    int weight = board.size()-i;
    for( int j=0; j<board[0].size(); ++j )
    {
      if( board[i][j] == 'O' )
      {
        answer += weight;
      }
    }
  }
  return answer;
}
auto tilt_i( std::vector<std::string> const& board, int di )
{
  std::vector<std::string> ret = board;
  for( auto &s : ret )
  {
    for( auto &ch : s ){ ch = '.'; }
  }
  const int start_i = di==1 ? 0 : board.size()-1;

  for( int j=0; j<board[0].size(); ++j )
  {
    int last_cube = start_i - di;
    int rock_count = 0;
    for( int i=start_i; (i>=0&&i<board.size()); i+=di )
    {
      const char ch = board[i][j];
      if( ch == '#' )
      {
        last_cube = i;
        rock_count = 0;
        ret[i][j] = '#';
      }else if( ch == 'O' )
      {
        ++rock_count;
        int rock_pos = last_cube + di*rock_count;

        ret[rock_pos][j] = 'O';
      }
    }
  }

  return ret;
}
auto tilt_j( std::vector<std::string> const& board, int dj )
{
  std::vector<std::string> ret = board;
  for( auto &s : ret )
  {
    for( auto &ch : s ){ ch = '.'; }
  }
  const int start_j = dj==1 ? 0 : board[0].size()-1;

  for( int i=0; i<board.size(); ++i )
  {
    int last_cube = start_j - dj;
    int rock_count = 0;
    for( int j=start_j; (j>=0&&j<board[0].size()); j+=dj )
    {
      const char ch = board[i][j];
      if( ch == '#' )
      {
        last_cube = j;
        rock_count = 0;
        ret[i][j] = '#';
      }else if( ch == 'O' )
      {
        ++rock_count;
        int rock_pos = last_cube + dj*rock_count;

        ret[i][rock_pos] = 'O';
      }
    }
  }

  return ret;
}
auto cycle( std::vector<std::string> board )
{
  // north
  board = tilt_i( board, 1 );

  // west
  board = tilt_j( board, 1 );

  // south
  board = tilt_i( board, -1 );

  // east
  return tilt_j( board, -1 );
}

int main()
{
  /*
  std::string str =
"O....#....\n"
"O.OO#....#\n"
".....##...\n"
"OO.#O....O\n"
".O.....O#.\n"
"O.#..O.#.#\n"
"..O..#O..O\n"
".......O..\n"
"#....###..\n"
"#OO..#....";
  std::istringstream input_file( str );
  */

  std::string line;
  std::vector<std::string> board;
  std::ifstream input_file( "../inputs/Day14.txt" );

  // transpose input lines
  while( std::getline(input_file,line) )
  {
    board.push_back( line );
  }

  std::cout << calculate_load(board) << "\n";

  int cycle_count = 0;
  std::map< std::vector<std::string>, int > history_map;
  std::vector< std::vector<std::string> > history;

  history.push_back( board );
  history_map[ board ] = 0;

  std::cout << cycle_count << ": " << calculate_load(board) << "\n";
  for( auto &s : board )
  {
    std::cout << s << "\n";
  }
  std::cout << "------\n";

  int max_count = 1000000000;
  while( cycle_count < max_count )
  {
    ++cycle_count;
    board = cycle( board );

    std::cout << cycle_count << ": " << calculate_load(board) << "\n";
    for( auto &s : board )
    {
      std::cout << s << "\n";
    }
    std::cout << "------\n";

    auto it = history_map.find( board );
    if( it == history_map.end() )
    {
      history_map[board] = cycle_count;
      history.push_back( board );
      continue;
    }else
    {
      std::cout << "cycle found: " << cycle_count << " is equals to " << it->second << "\n";

      int period_start = it->second;
      int period = cycle_count - period_start;
      int search_for = (max_count - period_start) % period;
      search_for += period_start;
      std::cout << "Thus, " << max_count << " is equals to " << search_for << "\n";

      board = history[search_for];
      break;
    }
  }


  std::cout << "Last---------------\n";
  for( auto &s : board )
  {
    std::cout << s << "\n";
  }
  std::cout << "------\n";

  std::cout << calculate_load( board ) << "\n";

  return 0;
}
