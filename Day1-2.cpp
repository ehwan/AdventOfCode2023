#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>


template < typename DataType >
struct Ahocorasick
{

struct Node
{
  std::map<char,Node> child;
  bool is_tail = false;
  DataType data;
  Node *fail = nullptr;
};
  Node root;

  void add( const char* str, DataType data )
  {
    Node *node = &root;
    const char *c = str;
    while( *c != 0 )
    {
      node = &node->child[*c];
      ++c;
    }
    node->is_tail = true;
    node->data = data;
  }

  // fail functions
  void construct_fail()
  {
    root.fail = &root;

    std::vector<Node*> queue;
    queue.push_back( &root );
    decltype(queue) pong;
    while( queue.empty() == false )
    {
      pong.clear();
      for( auto *q : queue )
      {
        for( auto &cp : q->child )
        {
          Node *c = &cp.second;

          // root의 자식의 fail은 root
          if( q == &root )
          {
            c->fail = q;
            pong.push_back( c );
            continue;
          }

          Node *fail = q->fail;
          while( 1 )
          {
            if( fail == &root ){ break; }
            if( fail->child.find(cp.first) == fail->child.end() )
            {
              fail = fail->fail;
            }
            else
            {
              break;
            }
          }
          auto it = fail->child.find( cp.first );
          if( it != fail->child.end() )
          {
            fail = &it->second;
          }
          c->fail = fail;
          pong.push_back( c );
        }
      }
      std::swap( queue, pong );
    }
  }

  std::vector<DataType> match( const char *str )
  {
    std::vector<DataType> ret;
    Node *node = &root;
    while( *str != 0 )
    {
      if( node->child.find(*str) == node->child.end() )
      {
        if( node == &root )
        {
          ++str;
        }else
        {
          node = node->fail;
        }
        continue;
      }

      node = &node->child[ *str ];
      if( node->is_tail )
      {
        ret.push_back( node->data );
        node = &root;
      }
      ++str;
    }

    return ret;
  }
};

int main()
{
  std::ifstream input_file( "../inputs/Day1.txt" );
  std::string line;

  Ahocorasick<int> ahocorasick;
  ahocorasick.add( "0", 0 );
  ahocorasick.add( "1", 1 );
  ahocorasick.add( "2", 2 );
  ahocorasick.add( "3", 3 );
  ahocorasick.add( "4", 4 );
  ahocorasick.add( "5", 5 );
  ahocorasick.add( "6", 6 );
  ahocorasick.add( "7", 7 );
  ahocorasick.add( "8", 8 );
  ahocorasick.add( "9", 9 );
  ahocorasick.add( "zero", 0 );
  ahocorasick.add( "one", 1 );
  ahocorasick.add( "two", 2 );
  ahocorasick.add( "three", 3 );
  ahocorasick.add( "four", 4 );
  ahocorasick.add( "five", 5 );
  ahocorasick.add( "six", 6 );
  ahocorasick.add( "seven", 7 );
  ahocorasick.add( "eight", 8 );
  ahocorasick.add( "nine", 9 );
  ahocorasick.construct_fail();

  int answer = 0;
  std::vector<int> parsed;
  while( std::getline(input_file,line) )
  {
    parsed = ahocorasick.match( line.c_str() );
    answer += parsed.front()*10 + parsed.back();
  }

  std::cout << answer << "\n";

  return 0;
}