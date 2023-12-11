#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
  int answer = 0;
  std::ifstream input_file( "../inputs/Day9.txt" );
  std::string line;
  while( std::getline(input_file,line) )
  {
    std::istringstream line_stream( std::move(line) );

    std::vector<int> numbers;
    int num;
    while( line_stream >> num ){ numbers.push_back( num ); }

    std::vector< std::vector<int> > sequences;
    sequences.push_back( std::move(numbers) );
    while( 1 )
    {
      // check all-zero
      bool all_zero = true;
      for( int x : sequences.back() )
      {
        if( x ){ all_zero = false; break; }
      }

      if( all_zero == false )
      {
        sequences.emplace_back( sequences.back().size()-1 );
        for( int i=0; i<sequences.back().size(); ++i )
        {
          sequences.back()[i] = (*(sequences.end()-2))[i+1] - (*(sequences.end()-2))[i];
        }
      }else {
        sequences.back().push_back( 0 );
        while( sequences.size() > 1 )
        {
          (*(sequences.end()-2)).push_back( (*(sequences.end()-2)).back() + sequences.back().back() );
          sequences.pop_back();
        }
        break;
      }
    }

    answer += sequences.back().back();
  }

  std::cout << answer << "\n";
}