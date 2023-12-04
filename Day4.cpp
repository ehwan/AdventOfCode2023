#include <iostream>
#include <fstream>
#include <sstream>
#include <set>


int main()
{
  std::ifstream input_file( "../inputs/Day4.txt" );

  int answer = 0;
  std::string line;
  while( std::getline(input_file,line) )
  {
    std::string dummy;

    std::istringstream line_stream( std::move(line) );
    // "Card"
    line_stream >> dummy;
    if( dummy != "Card" ){ break; }

    // "number:"
    line_stream >> dummy;

    std::set<int> winning;
    int left_num;
    while( line_stream >> left_num )
    {
      winning.insert( left_num );
    }

    // "|"
    line_stream.clear();
    line_stream >> dummy;

    int score = 0;
    int right_num;
    while( line_stream >> right_num )
    {
      if( winning.find(right_num) != winning.end() )
      {
        score = score ? 2*score : 1;
      }
    }

    answer += score;
  }


  std::cout << answer << "\n";
}