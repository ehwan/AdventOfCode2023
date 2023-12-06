#include <cstddef>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

using int_type = long long;

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

  std::string dummy;
  int_type int_type_;

  input_file >> dummy;
  std::string time_string;
  while( input_file >> int_type_ )
  {
    time_string += std::to_string(int_type_);
  }
  input_file.clear();

  input_file >> dummy;
  std::string distance_string;
  while( input_file >> int_type_ )
  {
    distance_string += std::to_string(int_type_);
  }

  int_type answer = solve( std::stoll( time_string ), std::stoll(distance_string) );


  std::cout << answer << "\n";
}