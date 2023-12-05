#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using int_type = long long;

struct range_map
{
  int_type src, dst, length;

  int_type operator()( int_type x ) const
  {
    if( src <= x && x < src+length )
    {
      return dst + (x-src);
    }
    return -1;
  }
};
struct range_maps
{
  std::vector< range_map > data;

  int_type operator()( int_type x ) const
  {
    for( auto r : data )
    {
      if( r(x) != -1 ){ return r(x); }
    }
    return -1;
  }
};

int main()
{
  std::ifstream input_file( "../inputs/Day5.txt" );

  int_type int_type_;
  std::string dummy;
  // "seeds"
  input_file >> dummy;

  std::vector<int_type> seeds;
  while( input_file >> int_type_ )
  {
    seeds.push_back( int_type_ );
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
    std::vector<int_type> ret;
    for( auto i : seeds )
    {
      auto f = map(i);
      if( f != -1 ){ ret.push_back(f); }
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

  std::cout << *std::min_element(seeds.begin(), seeds.end() ) << "\n";
}