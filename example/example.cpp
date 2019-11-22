#define CPPMATH_OSTREAM_OPERATOR
#define CPPMATH_SWIZZLE_FUNCTIONS
#include "cppmath/vec/vec2.h"
#include "cppmath/vec/vec_types.h"
#include <iostream>
#include <array>

using namespace math;

int main(int, char*[])
{
  dvec2 a(1.0, 2.0);
  ivec2 b(3, 4);
  std::cout << a << "\n";
  a.yx() = b.yy();
  std::cout << a.xy() << "\n";
  return 0;
}
