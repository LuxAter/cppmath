#include <map>
#include <string>
#include <vector>

#include "doctest.h"
#include "linalg/type_tools.h"
#include "timer.h"

using namespace linalg;

struct MyTestType {};

TEST_CASE("type_name") {
  CHECK_EQ(sfinae::type_name<int>(), "int");
  CHECK_EQ(
      sfinae::type_name<std::vector<std::map<std::string, float>>>(),
      "std::vector<std::map<std::__cxx11::basic_string<char, "
      "std::char_traits<char>, std::allocator<char> >, float, "
      "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, "
      "std::allocator<char> > >, "
      "std::allocator<std::pair<std::__cxx11::basic_string<char, "
      "std::char_traits<char>, std::allocator<char> > const, float> > >, "
      "std::allocator<std::map<std::__cxx11::basic_string<char, "
      "std::char_traits<char>, std::allocator<char> >, float, "
      "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, "
      "std::allocator<char> > >, "
      "std::allocator<std::pair<std::__cxx11::basic_string<char, "
      "std::char_traits<char>, std::allocator<char> > const, float> > > > >");
  CHECK_EQ(sfinae::type_name<MyTestType>(), "MyTestType");
}

TEST_CASE("has_eq") {
  CHECK_EQ(sfinae::has_eq<int>::value, true);
  CHECK_EQ(sfinae::has_eq<int, float>::value, true);
  CHECK_EQ(sfinae::has_eq<int, std::string>::value, false);
  CHECK_EQ(sfinae::has_eq<std::string>::value, true);
  CHECK_EQ(sfinae::has_eq<MyTestType>::value, false);
}

TEST_CASE("has_neq") {
  CHECK_EQ(sfinae::has_neq<int>::value, true);
  CHECK_EQ(sfinae::has_neq<int, float>::value, true);
  CHECK_EQ(sfinae::has_neq<int, std::string>::value, false);
  CHECK_EQ(sfinae::has_neq<std::string>::value, true);
  CHECK_EQ(sfinae::has_neq<MyTestType>::value, false);
}

TEST_CASE("has_lt") {
  CHECK_EQ(sfinae::has_lt<int>::value, true);
  CHECK_EQ(sfinae::has_lt<int, float>::value, true);
  CHECK_EQ(sfinae::has_lt<int, std::string>::value, false);
  CHECK_EQ(sfinae::has_lt<std::string>::value, true);
  CHECK_EQ(sfinae::has_lt<MyTestType>::value, false);
}

TEST_CASE("has_gt") {
  CHECK_EQ(sfinae::has_gt<int>::value, true);
  CHECK_EQ(sfinae::has_gt<int, float>::value, true);
  CHECK_EQ(sfinae::has_gt<int, std::string>::value, false);
  CHECK_EQ(sfinae::has_gt<std::string>::value, true);
  CHECK_EQ(sfinae::has_gt<MyTestType>::value, false);
}

TEST_CASE("has_leq") {
  CHECK_EQ(sfinae::has_leq<int>::value, true);
  CHECK_EQ(sfinae::has_leq<int, float>::value, true);
  CHECK_EQ(sfinae::has_leq<int, std::string>::value, false);
  CHECK_EQ(sfinae::has_leq<std::string>::value, true);
  CHECK_EQ(sfinae::has_leq<MyTestType>::value, false);
}

TEST_CASE("has_geq") {
  CHECK_EQ(sfinae::has_geq<int>::value, true);
  CHECK_EQ(sfinae::has_geq<int, float>::value, true);
  CHECK_EQ(sfinae::has_geq<int, std::string>::value, false);
  CHECK_EQ(sfinae::has_geq<std::string>::value, true);
  CHECK_EQ(sfinae::has_geq<MyTestType>::value, false);
}
