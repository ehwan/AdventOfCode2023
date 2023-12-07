#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

std::map<char,int> char_order;

struct hand_t
{
  int order;
  std::vector<int> cards;
  int bid;
  hand_t( std::string const& _cards, int _bid )
  {
    bid = _bid;
    std::vector<int> cards_;
    cards_.resize( _cards.size() );
    std::transform( _cards.begin(), _cards.end(), cards_.begin(),
      [&]( char ch ){ return char_order[ch]; } );

    cards = cards_;

    std::sort( cards_.begin(), cards_.end(), std::greater<int>() );

    std::vector<int> uniques;
    int jcount = 0;
    int prev = -2;
    for( int i=0; i<cards_.size(); ++i )
    {
      if( cards_[i] == char_order['J'] ){ ++jcount; }
      if( prev != cards_[i] )
      {
        uniques.push_back( 1 );
      }else {
        uniques.back()++;
      }
      prev = cards_[i];
    }

    sort( uniques.begin(), uniques.end(), std::greater<int>() );
    if( jcount > 0 && jcount < 5 )
    {
      uniques.erase( std::find( uniques.begin(), uniques.end(), jcount ) );
      uniques.front() += jcount;
    }
    if( uniques[0] == 1 )
    {
      order = 0;
    }else if( uniques[0] == 2 )
    {
      if( uniques[1] == 1 )
      {
        order = 1;
      }else {
        order = 2;
      }
    }else if( uniques[0] == 3 )
    {
      if( uniques[1] == 2 )
      {
        order = 4;
      }else {
        order =3;
      }
    }else if( uniques[0] == 4 )
    {
      order = 5;
    }else {
      order = 6;
    }
  }

  bool operator< ( hand_t const& rhs ) const
  {
    if( order < rhs.order ){ return true; }
    if( order > rhs.order ){ return false; }
    return std::lexicographical_compare( cards.begin(), cards.end(), rhs.cards.begin(), rhs.cards.end() );
  }
};

int main()
{
  char_order['2'] = 0;
  char_order['3'] = 1;
  char_order['4'] = 2;
  char_order['5'] = 3;
  char_order['6'] = 4;
  char_order['7'] = 5;
  char_order['8'] = 6;
  char_order['9'] = 7;
  char_order['T'] = 8;
  char_order['J'] = -1;
  char_order['Q'] = 10;
  char_order['K'] = 11;
  char_order['A'] = 12;

  std::ifstream input_file( "../inputs/Day7.txt" );

  std::vector<hand_t> hands;

  std::string cards;
  while( input_file >> cards )
  {
    int bid;
    input_file >> bid;

    hands.emplace_back( cards, bid );
  }

  std::sort( hands.begin(), hands.end() );

  int answer = 0;
  for( int i=0; i<hands.size(); ++i )
  {
    answer += hands[i].bid * (i+1);
  }

  std::cout << answer << "\n";
}