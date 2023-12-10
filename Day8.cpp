#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{
  std::ifstream input_file( "../inputs/Day8.txt" );

  std::string command;
  std::getline( input_file, command );

  std::string root, left, right, dummy;

  std::map<std::string,std::string> lefts, rights;
  while( input_file >> root )
  {
    input_file >> dummy;
    input_file >> left;
    input_file >> right;

    std::string left_( left.begin()+1, left.begin()+1+3 );
    left = std::move(left_);
    std::string right_( right.begin(), right.end()-1 );
    right = std::move(right_);

    lefts[root] = left;
    rights[root] = right;
  }

  int answer = 0;
  int i = 0;
  std::string cur = "AAA";
  while( cur != "ZZZ" )
  {
    if( command[i] == 'L' )
    {
      cur = lefts[cur];
    }else {
      cur = rights[cur];
    }
    ++i;
    if( i == command.size() ){ i = 0; }
    ++answer;
  }
  std::cout << answer << "\n";
}