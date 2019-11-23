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

#ifndef LINALG_VEC2_H_
#define LINALG_VEC2_H_

#include <cstdlib>
#include <stdexcept>

#ifdef LINALG_OSTREAM_OPERATOR
#include <iostream>
#endif
#ifdef LINALG_SWIZZLE_FUNCTION
#include "swizzle_functions.h"
#endif

#include "../type_tools.h"
#include "vec_base.h"

namespace linalg {
  template <typename T>
  using vec2 = vec<T, 2>;

  template <typename T>
  struct vec<T, 2> {
    typedef T value_type;
    typedef std::size_t size_type;

    vec() : x(), y() {}
    vec(const value_type& v) : x(v), y(v) {}
    vec(const value_type& x, const value_type& y) : x(x), y(y) {}
    template <
        typename U, std::size_t N,
        typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
    vec(const vec<U, N>& copy) : x(copy.x), y(copy.y) {}

    constexpr value_type& r() { return x; }
    constexpr const value_type& r() const { return x; }
    constexpr value_type& g() { return y; }
    constexpr const value_type& g() const { return y; }

#ifdef LINALG_SWIZZLE_FUNCTION
    SWIZZLE_2()
#endif

    static constexpr size_type length() { return 2; }
    static constexpr size_type size() { return 2; }
    constexpr value_type& operator[](const size_type& i) {
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
    constexpr const value_type& operator[](const size_type& i) const {
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

    value_type x, y;
  };

  template <typename T, typename U,
            typename = std::enable_if_t<sfinae::has_eq<T, U>::value>>
  constexpr inline bool operator==(const vec<T, 2>& lhs, const vec<U, 2>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  template <typename T, typename U,
            typename = std::enable_if_t<sfinae::has_eq<T, U>::value>>
  constexpr inline bool operator!=(const vec<T, 2>& lhs, const vec<U, 2>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T, typename U,
            typename = std::enable_if_t<sfinae::has_lt<T, U>::value>>
  constexpr inline bool operator<(const vec<T, 2>& lhs, const vec<U, 2>& rhs) {
    return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
  }
  template <typename T, typename U,
            typename = std::enable_if_t<sfinae::has_lt<T, U>::value>>
  constexpr inline bool operator>(const vec<T, 2>& lhs, const vec<U, 2>& rhs) {
    return rhs < lhs;
  }
  template <typename T, typename U,
            typename = std::enable_if_t<sfinae::has_lt<T, U>::value>>
  constexpr inline bool operator<=(const vec<T, 2>& lhs, const vec<U, 2>& rhs) {
    return !(rhs < lhs);
  }
  template <typename T, typename U,
            typename = std::enable_if_t<sfinae::has_lt<T, U>::value>>
  constexpr inline bool operator>=(const vec<T, 2>& lhs, const vec<U, 2>& rhs) {
    return !(lhs < rhs);
  }

  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
                                        
  constexpr inline vec<T, 2> operator+(const vec<T, 2>& lhs, const U& rhs) {
    return {lhs.x + rhs, lhs.y + rhs};
  }
  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        sfinae::has_plus<T, U>::value>>
  constexpr inline vec<T, 2> operator+(const vec<T, 2>& lhs,
                                       const vec<U, 2>& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
  }
  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        sfinae::has_plus<T, U>::value>>
  constexpr inline vec<T, 2> operator-(const vec<T, 2>& lhs, const U& rhs) {
    return {lhs.x - rhs, lhs.y - rhs};
  }
  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        sfinae::has_plus<T, U>::value>>
  constexpr inline vec<T, 2> operator-(const vec<T, 2>& lhs,
                                       const vec<U, 2>& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
  }
  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        sfinae::has_plus<T, U>::value>>
  constexpr inline vec<T, 2> operator*(const vec<T, 2>& lhs, const U& rhs) {
    return {lhs.x * rhs, lhs.y * rhs};
  }
  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        sfinae::has_plus<T, U>::value>>
  constexpr inline vec<T, 2> operator*(const vec<T, 2>& lhs,
                                       const vec<U, 2>& rhs) {
    return {lhs.x * rhs.x, lhs.y * rhs.y};
  }
  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        sfinae::has_plus<T, U>::value>>
  constexpr inline vec<T, 2> operator/(const vec<T, 2>& lhs, const U& rhs) {
    return {lhs.x / rhs, lhs.y / rhs};
  }
  template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value &&
                                        sfinae::has_plus<T, U>::value>>
  constexpr inline vec<T, 2> operator/(const vec<T, 2>& lhs,
                                       const vec<U, 2>& rhs) {
    return {lhs.x / rhs.x, lhs.y / rhs.y};
  }

#ifdef LINALG_OSTREAM_OPERATOR
  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const vec<T, 2>& rhs) {
    return out << '<' << rhs.x << ',' << rhs.y << '>';
  }
#endif

}  // namespace linalg

#endif  // LINALG_VEC2_H_
