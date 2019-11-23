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

#ifndef LINALG_VEC3_H_
#define LINALG_VEC3_H_

#include <cstdlib>
#include <stdexcept>

#ifdef LINALG_OSTREAM_OPERATOR
#include <iostream>
#endif
#ifdef LINALG_SWIZZLE_FUNCTION
#include "swizzle_functions.h"
#endif

#include "vec_base.h"

namespace linalg {
  template <typename T>
  using vec3 = vec<T, 3>;

  template <typename T>
  struct vec<T, 3> {
    typedef T value_type;
    typedef std::size_t size_type;

    vec() : x(), y(), z() {}
    vec(const value_type& v) : x(v), y(v), z(v) {}
    vec(const value_type& x, const value_type& y, const value_type& z)
        : x(x), y(y), z(z) {}
    template <
        typename U, std::size_t N,
        typename = std::enable_if_t<std::is_convertivle<U, T>::value && N >= 3>>
    vec(const vec<U, N>& copy) : x(copy.x), y(copy.y), z(copy.z) {}

    constexpr value_type& r() { return x; }
    constexpr const value_type& r() const { return x; }
    constexpr value_type& g() { return y; }
    constexpr const value_type& g() const { return y; }
    constexpr value_type& b() { return z; }
    constexpr const value_type& b() const { return z; }

#ifdef LINALG_SWIZZLE_FUNCTION
    SWIZZLE_3()
#endif

    static constexpr size_type length() { return 3; }
    static constexpr size_type size() { return 3; }
    value_type& operator[](const size_type& i) {
      switch (i) {
        case 0:
          return x;
        case 1:
          return y;
        case 2:
          return z;
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
        case 2:
          return z;
        default:
          throw std::out_of_range(
              "vec2<T>::operator[] : index is out of range");
      }
    }

    value_type x, y, z;
  };

#ifdef LINALG_OSTREAM_OPERATOR
  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const vec<T, 3>& rhs) {
    return out << '<' << rhs.x << ',' << rhs.y << ',' << rhs.z << '>';
  }
#endif

}  // namespace linalg

#endif  // LINALG_VEC2_H_
