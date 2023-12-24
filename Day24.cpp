#include <iostream>
#include <sstream>
#include <fstream>
#include <string_view>
#include <vector>

using int_type = long long;
struct ivec3_t
{
  int_type x, y, z;
};
std::ostream& operator<<( std::ostream& stream, ivec3_t v )
{
  return stream << v.x << "," << v.y << "," << v.z;
}

ivec3_t parse_ivec3( std::string_view str )
{
  auto comma1 = str.find( ',' );
  auto comma2 = str.find( ',', comma1+1 );

  ivec3_t ret;
  ret.x = std::strtoll( str.data(), nullptr, 10 );
  ret.y = std::strtoll( str.data()+comma1+2, nullptr, 10 );
  ret.z = std::strtoll( str.data()+comma2+2, nullptr, 10 );
  return ret;
}

struct imomentum_t
{
  ivec3_t pos;
  ivec3_t vel;
};
imomentum_t parse_line( std::string_view str )
{
  auto at_pos = str.find( '@' );

  imomentum_t ret;
  ret.pos = parse_ivec3( str.substr(0,at_pos) );
  ret.vel = parse_ivec3( str.substr(at_pos+2) );

  return ret;
}
struct intersect_output_t
{
  int_type determinant;
  int_type a;
  int_type b;
};
intersect_output_t intersect( imomentum_t const& a, imomentum_t const& b )
{
  /*
   * ** ONLY FOR X-Y AXIS **
   * a.pos + a_time * a.vel = b.pos + b_time * b.vel
   * ( a.vel -b.vel ) ( a_time b_time )^T = b.pos - a.pos
   *
   * ( a_time b_time )^T = ( a.vel -b.vel )^-1 * (b.pos - a.pos)
   * x = A^-1 * b
   */

  intersect_output_t out;


  int_type A[2][2] =
  {
    { a.vel.x, -b.vel.x },
    { a.vel.y, -b.vel.y }
  };
  out.determinant = A[0][0]*A[1][1] - A[0][1]*A[1][0];
  if( out.determinant == 0 )
  {
    return out;
  }
  int_type b_[2] =
  {
    b.pos.x - a.pos.x,
    b.pos.y - a.pos.y
  };
  int_type adj_A[2][2] =
  {
    { A[1][1], -A[0][1] },
    {-A[1][0],  A[0][0] }
  };

  out.a = adj_A[0][0]*b_[0] + adj_A[0][1]*b_[1];
  out.b = adj_A[1][0]*b_[0] + adj_A[1][1]*b_[1];

  return out;
}


int main()
{
  //std::string str =
//"19, 13, 30 @ -2,  1, -2\n"
//"18, 19, 22 @ -1, -1, -2\n"
//"20, 25, 34 @ -2, -2, -4\n"
//"12, 31, 28 @ -1, -2, -1\n"
//"20, 19, 15 @  1, -5, -3";
  //std::istringstream input_file( str );
  std::ifstream input_file( "../inputs/Day24.txt" );

  std::string line;
  std::vector< imomentum_t > hailstones;
  while( std::getline(input_file,line) )
  {
    auto h = parse_line( line );
    hailstones.push_back( h );
  }

  const int_type MIN_BOUND = 200000000000000ll;
  const int_type MAX_BOUND = 400000000000000ll;
  //const int_type MIN_BOUND = 7;
  //const int_type MAX_BOUND = 27;

  int answer = 0;
  for( int i=0; i<hailstones.size(); ++i )
  {
    for( int j=i+1; j<hailstones.size(); ++j )
    {
      auto a = hailstones[i];
      auto b = hailstones[j];
      auto hit = intersect( a,  b );

      if( hit.determinant == 0 )
      {
        std::cout << "Parallel\n";
        continue;
      }

      if( 
        ( hit.determinant<0 && (hit.a>0 || hit.b>0 ) ) ||
        ( hit.determinant>0 && (hit.a<0 || hit.b<0 ) )
      )
      {
        std::cout << "Past\n";
        continue;
      }

      double px = a.pos.x + a.vel.x*(double)hit.a/hit.determinant;
      double py = a.pos.y + a.vel.y*(double)hit.a/hit.determinant;
      if( MIN_BOUND <= px && px <= MAX_BOUND && MIN_BOUND <= py && py <= MAX_BOUND )
      {
        ++answer;
        continue;
      }
      /*

      // MIN_BOUND <= pos + vel*hit.a/Det <= MAX_BOUND
      // (MIN_BOUND - pos)*Det <= vel*hit.a <= (MAX_BOUND-pos)*Det

      int_type minx = (MIN_BOUND - a.pos.x)*hit.determinant;
      int_type maxx = (MAX_BOUND - a.pos.x)*hit.determinant;
      int_type miny = (MIN_BOUND - a.pos.y)*hit.determinant;
      int_type maxy = (MAX_BOUND - a.pos.y)*hit.determinant;
      int_type px = a.vel.x*hit.a;
      int_type py = a.vel.y*hit.a;
      if( hit.determinant > 0 &&
          ( minx <= px && px <= maxx ) &&
          ( miny <= py && py <= maxy ) )
      {
        ++answer;
        std::cout << "Hit!\n";
        continue;
      }
      if( hit.determinant < 0 &&
          ( minx >= px && px >= maxx ) &&
          ( miny >= py && py >= maxy ) )
      {
        ++answer;
        std::cout << "Hit!\n";
        continue;
      }
      */
    }
  }

  std::cout << answer << "\n";
}
