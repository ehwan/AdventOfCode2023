#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>

int main()
{
//   std::string str =
//   "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n"
// "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n"
// "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n"
// "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n"
// "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n"
// "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11";
  // std::istringstream input_file( str );
  std::ifstream input_file( "../inputs/Day4.txt" );

  std::string line;
  std::vector<int> win_count;
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

    int count = 0;
    int right_num;
    while( line_stream >> right_num )
    {
      if( winning.find(right_num) != winning.end() )
      {
        ++count;
      }
    }

    win_count.push_back( count );
  }

  std::vector<int> card_counts;
  card_counts.resize( win_count.size(), 1 );
  card_counts[0] = 1;

  int answer = 0;

  std::cout << "WinCount-----\n";
  for( auto w : win_count ){ std::cout << w << "\n"; }
  std::cout << "---------\n";

  for( int i=0; i<win_count.size(); ++i )
  {
    answer += card_counts[i];
    std::cout << card_counts[i] << "\n";
    for( int j=0; j<win_count[i]; ++j )
    {
      int x = i + j + 1;
      if( x >= win_count.size() ){ break; }
      card_counts[x] += card_counts[i];
    }
  }


  std::cout << answer << "\n";
}