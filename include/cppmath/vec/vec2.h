/*
 * Copyright (c) 2019 Rasmussen, Arden <ardenrasmussen@lclark.edu>
 * Author: Rasmussen, Arden <ardenrasmussen@lclark.edu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CPPMATH_VEC2_H_
#define CPPMATH_VEC2_H_

#include <cstdlib>
#include <stdexcept>

#ifdef CPPMATH_OSTREAM_OPERATOR
#include <iostream>
#endif
#include "swizzle_functions.h"

#include "vec_base.h"

namespace math {
  template <typename T>
  using vec2 = vec<T, 2>;

  template <typename T>
  struct vec<T, 2> {
    typedef T value_type;
    typedef std::size_t size_type;

    vec() : x(), y() {}
    vec(const value_type& v) : x(v), y(v) {}
    vec(const value_type& x, const value_type& y) : x(x), y(y) {}
    // vec(const value_type&& x, const value_type&& y) : x(x), y(y) {}

// #ifdef CPPMATH_SWIZZLE_FUNCTION
    SWIZZLE_2_2()
    /* TODO: Add swizzle function <07-11-19, Arden Rasmussen> */
// #endif

    static constexpr size_type length() { return 2; }
    static constexpr size_type size() { return 2; }
    value_type& operator[](const size_type& i) {
      switch (i) {
        case 0:
          return x;
        case 1:
          return y;
        default:
          throw std::out_of_range(
              "vec2<T>::operator[] : index is out of range");
      }
    }
    const value_type& operator[](const size_type& i) const {
      switch (i) {
        case 0:
          return x;
        case 1:
          return y;
        default:
          throw std::out_of_range(
              "vec2<T>::operator[] : index is out of range");
      }
    }

    union {
      value_type x, r;
    };
    union {
      value_type y, g;
    };
  };

#ifdef CPPMATH_OSTREAM_OPERATOR
  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const vec<T, 2>& rhs) {
    return out << '<' << rhs.x << ',' << rhs.y << '>';
  }
#endif

}  // namespace math

#endif  // CPPMATH_VEC2_H_
