#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

using int_type = int;

int_type solve( int_type T, int_type D )
{
  if( T*T-4*D < 0 ){ return 0; }
  double Det = T*T-4.0*D;
  Det = std::sqrt(Det);

  double A = (T - Det)*0.5;
  double B = (T + Det)*0.5;

  int_type A_ = (int_type)std::ceil(A);
  int_type B_ = (int_type)std::floor(B);
  return B_-A_+1;
}

int main()
{
  std::ifstream input_file( "../inputs/Day6.txt" );

  std::vector<int_type> times;
  std::vector<int_type> distances;
  std::string dummy;
  int_type int_type_;

  input_file >> dummy;
  while( input_file >> int_type_ )
  {
    times.push_back( int_type_ );
  }
  input_file.clear();

  input_file >> dummy;
  while( input_file >> int_type_ )
  {
    distances.push_back( int_type_ );
  }

  int_type answer = 1;
  for( int i=0; i<times.size(); ++i )
  {
    answer *= solve( times[i], distances[i] );
  }

  std::cout << answer << "\n";
}