#include "linalg/vec/vec2.h"

#include <map>
#include <string>
#include <vector>

#include "doctest.h"

using namespace linalg;
typedef vec2<double> dvec2;

TEST_CASE("Constructor") {
  dvec2 a;
  dvec2 b(1.0);
  dvec2 c(2.0, 3.0);
  dvec2 d(c);
  CHECK((a.x == 0.0 && a.y == 0.0));
  CHECK((b.x == 1.0 && b.y == 1.0));
  CHECK((c.x == 2.0 && c.y == 3.0));
  CHECK((d.x == 2.0 && d.y == 3.0));
}

TEST_CASE("Value Access") {
  dvec2 a(2.0, 3.0);
  CHECK((a.x == 2.0 && a.y == 3.0));
  CHECK((a.r() == 2.0 && a.g() == 3.0));
  CHECK((a[0] == 2.0 && a[1] == 3.0));
  const dvec2 b(2.0, 3.0);
  CHECK((b.x == 2.0 && b.y == 3.0));
  CHECK((b.r() == 2.0 && b.g() == 3.0));
  CHECK((b[0] == 2.0 && b[1] == 3.0));
}

TEST_CASE("Value Modification") {
  dvec2 a(2.0, 3.0);
  CHECK((a.x == 2.0 && a.y == 3.0));
  a.x = 4.0;
  CHECK((a.x == 4.0 && a.y == 3.0));
  a.g() = 1.0;
  CHECK((a.x == 4.0 && a.y == 1.0));
  a[0] = 0.1;
  CHECK((a.x == 0.1 && a.y == 1.0));
}

TEST_CASE("LOGICAL OPERATORS") {
  dvec2 a(2.0, 2.0), b(2.0, 3.0), c(3.0, 2.0), d(3.0, 3.0);

  CHECK_EQ(a, dvec2{2.0, 2.0});
  CHECK_NE(a, dvec2{1.0, 1.0});

  CHECK_EQ(a, a);
  CHECK_EQ(b, b);
  CHECK_EQ(c, c);
  CHECK_EQ(d, d);

  CHECK_NE(a, b);
  CHECK_NE(a, c);
  CHECK_NE(a, d);
  CHECK_NE(b, a);
  CHECK_NE(b, c);
  CHECK_NE(b, d);
  CHECK_NE(c, a);
  CHECK_NE(c, b);
  CHECK_NE(c, d);
  CHECK_NE(d, a);
  CHECK_NE(d, b);
  CHECK_NE(d, c);

  CHECK_GT(d, a);
  CHECK_GT(d, b);
  CHECK_GT(d, c);
  CHECK_GT(c, a);
  CHECK_GT(c, b);
  CHECK_GT(b, a);

  CHECK_LT(a, b);
  CHECK_LT(a, c);
  CHECK_LT(a, d);
  CHECK_LT(b, c);
  CHECK_LT(b, d);
  CHECK_LT(c, d);

  CHECK_GE(a, a);
  CHECK_GE(b, a);
  CHECK_GE(b, b);
  CHECK_GE(c, a);
  CHECK_GE(c, b);
  CHECK_GE(c, c);
  CHECK_GE(d, a);
  CHECK_GE(d, b);
  CHECK_GE(d, c);
  CHECK_GE(d, d);

  CHECK_LE(a, a);
  CHECK_LE(a, b);
  CHECK_LE(a, c);
  CHECK_LE(a, d);
  CHECK_LE(b, b);
  CHECK_LE(b, c);
  CHECK_LE(b, d);
  CHECK_LE(c, c);
  CHECK_LE(c, d);
  CHECK_LE(d, d);
}

TEST_CASE("Operations") {
  dvec2 a(3.0, 2.0), b(-3.0, 4.0);
  // CHECK_EQ(a + 1, dvec2{4.0, 3.0});
  // CHECK_EQ(a - 1, dvec2{3.0, 2.0});
  // CHECK_EQ(a * 2, dvec2{6.0, 4.0});
  // CHECK_EQ(a / 2, dvec2{1.5, 1.0});
  // CHECK_EQ(a + b, dvec2{0.0, 6.0});
  // CHECK_EQ(a - b, dvec2{9.0, -2.0});
  // CHECK_EQ(a * b, dvec2{-9.0, 8.0});
  // CHECK_EQ(a / b, dvec2{1.0, 0.5});
}
