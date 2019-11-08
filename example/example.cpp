#include "cppmath/type_tool.h"
#include <iostream>

using namespace math;

int main(int, char*[])
{

  bool v = sfinae::has_eq<int>::value;
  return 0;
}
