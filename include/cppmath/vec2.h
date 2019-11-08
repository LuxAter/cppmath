/*
 * Copyright (c) 2019 Rasmussen, Arden <ardenrasmussen@lclark.edu>
 * Author: Rasmussen, Arden <ardenrasmussen@lclark.edu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CPPMATH_VEC2_H_
#define CPPMATH_VEC2_H_

#include "type_vector.h"

namespace math {
template <typename T>
struct vec<T, 2> {
  typedef T value_type;
  typedef std::size_t length_type;
  typedef vec<T, 2> type;

  union {
    T x, r, s;
  };
  union {
    T y, g, t;
  };

#ifdef CPPMATH_SWIZZLE_FUNCTION
  /* TODO: Add swizzle function <07-11-19, Arden Rasmussen> */
#endif

  static constexpr length_type length()
  {
    return 2;
  }
  T& operator[](const length_type& i)
  {
    assert(i >= 0 && i < this->length());
    switch (i) {
    default:
    case 0:
      return x;
    case 1:
      return y;
    }
  }
  const T& operator[](const length_type& i) const
  {
    assert(i >= 0 && i < this->length());
    switch (i) {
    default:
    case 0:
      return x;
    case 1:
      return y;
    }
  }
};
} // namespace math

#endif // CPPMATH_VEC2_H_
