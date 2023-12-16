#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int hash( std::string str )
{
  int answer = 0;
  for( int ch : str )
  {
    if( ch == '\n' ){ break; }
    answer += ch;
    answer *= 17;
    answer %= 256;
  }
  return answer;
}

int main()
{
  // std::string str =
  // "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7";
  // std::istringstream input_file( str );

  std::ifstream input_file( "../inputs/Day15.txt" );

  int answer = 0;
  std::string token;
  while( std::getline(input_file,token,',') )
  {
    answer += hash(token);
  }

  std::cout << answer << "\n";
}