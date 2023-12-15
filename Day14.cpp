#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

int solve_line( std::string const& s )
{
  int last_cube = -1;
  int rock_count = 0;

  int answer = 0;

  for( int i=0; i<s.size(); ++i )
  {
    if( s[i] == '#' )
    {
      last_cube = i;
      rock_count = 0;
    }else if( s[i] == 'O' )
    {
      ++rock_count;
      int rock_pos = last_cube + rock_count;
      int load = s.size() - rock_pos;

      answer += load;
    }
  }
  return answer;
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
    board.resize( line.size() );
    for( int i=0; i<line.size(); ++i )
    {
      board[i].push_back( line[i] );
    }
  }

  int answer = 0;
  for( auto &s : board )
  {
    answer += solve_line( s );
  }

  std::cout << answer << "\n";
  return 0;
}
