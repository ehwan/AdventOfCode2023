#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

int main()
{
  std::ifstream input_file( "../inputs/Day2.txt" );

  int answer = 0;
  while( input_file )
  {
    std::string dummy_token;
    // "Game"
    input_file >> dummy_token;
    if( dummy_token != "Game" ){ break; }

    int gameid;
    input_file >> gameid;

    // ":"
    input_file >> dummy_token;

    std::string line;
    std::getline( input_file, line );

    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;
    std::string game;
    std::istringstream line_stream( std::move(line) );
    while( std::getline(line_stream, game, ';') )
    {
      std::istringstream game_stream( std::move(game) );

      std::string cube;
      while( std::getline( game_stream, cube, ',' ) )
      {
        int count;
        std::string color;
        std::istringstream cube_stream( std::move(cube) );
        cube_stream >> count >> color;

        if( color == "red" )
        {
          max_red = std::max( max_red, count );
        }else if( color == "green" )
        {
          max_green = std::max( max_green, count );
        }else if( color == "blue" )
        {
          max_blue = std::max( max_blue, count );
        }
      }
    }

    answer += max_red * max_green * max_blue;
  }

  std::cout << answer << "\n";

  return 0;
}