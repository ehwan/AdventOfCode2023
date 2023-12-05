#include <fstream>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

using int_type = long long;

struct seed_t
{
  int_type begin, end;

  bool valid() const
  {
    return begin != -1;
  }
};
struct range_map
{
  int_type src, dst, length;

  seed_t operator()( seed_t x ) const
  {
    auto beg = std::max( x.begin, src );
    auto end = std::min( src+length, x.end );
    if( beg >= end ){ return {-1,-1}; }
    return { beg-src+dst, end-src+dst };
  }
};
struct range_maps
{
  std::vector< range_map > data;

  std::vector<seed_t> operator()( seed_t x ) const
  {
    std::vector<seed_t> ret;
    for( auto r : data )
    {
      auto d = r(x);
      if( d.valid() )
      {
        ret.push_back( d );
      }
    }
    return ret;
  }
};

int main()
{
  std::ifstream input_file( "../inputs/Day5.txt" );

  int_type int_type_;
  std::string dummy;
  // "seeds"
  input_file >> dummy;

  std::vector<seed_t> seeds;
  while( input_file >> int_type_ )
  {
    int_type count;
    input_file >> count;
    seeds.push_back( {int_type_, int_type_+count} );
  }
  input_file.clear();

  auto parse_range_maps = [&]() -> range_maps
  {
    range_maps ret;
    int_type int_type_;
    range_map range;
    input_file >> dummy;
    std::cout << dummy << " ";
    input_file >> dummy;
    std::cout << dummy << "\n";
    while( input_file >> int_type_ )
    {
      range.dst = int_type_;
      input_file >> int_type_;
      range.src = int_type_;
      input_file >> int_type_;
      range.length = int_type_;
      ret.data.push_back( range );
    }
    input_file.clear();
    return ret;
  };

  auto seed_to_soil = parse_range_maps();
  auto soil_to_fert = parse_range_maps();
  auto fert_to_water = parse_range_maps();
  auto water_to_light = parse_range_maps();
  auto light_to_temp = parse_range_maps();
  auto temp_to_hum = parse_range_maps();
  auto hum_to_loc = parse_range_maps();

  auto filter = [&]( range_maps const& map )
  {
    std::vector<seed_t> ret;
    for( auto i : seeds )
    {
      auto f = map(i);
      ret.insert( ret.end(), f.begin(), f.end() );
    }
    return ret;
  };

  seeds = filter( seed_to_soil );
  seeds = filter( soil_to_fert );
  seeds = filter( fert_to_water );
  seeds = filter( water_to_light );
  seeds = filter( light_to_temp );
  seeds = filter( temp_to_hum );
  seeds = filter( hum_to_loc );

  int_type minn = std::numeric_limits<int_type>::max();
  for( auto s : seeds )
  {
    minn = std::min( minn, s.begin );
  }

  std::cout << minn << "\n";
}