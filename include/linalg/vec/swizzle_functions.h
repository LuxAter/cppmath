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

#ifndef LINALG_SWIZZLE_FUNCTIONS_H_
#define LINALG_SWIZZLE_FUNCTIONS_H_

#include <cstdlib>
#include <stdexcept>

#define SWIZZLE_2_BASE(a, b)                                          \
  inline swizzle<value_type, 2> a##a() { return {a, a}; }             \
  inline swizzle<const value_type, 2> a##a() const { return {a, a}; } \
  inline swizzle<value_type, 2> a##b() { return {a, b}; }             \
  inline swizzle<const value_type, 2> a##b() const { return {a, b}; } \
  inline swizzle<value_type, 2> b##a() { return {b, a}; }             \
  inline swizzle<const value_type, 2> b##a() const { return {b, a}; } \
  inline swizzle<value_type, 2> b##b() { return {b, b}; }             \
  inline swizzle<const value_type, 2> b##b() const { return {b, b}; }

#define SWIZZLE_2_2()  \
  SWIZZLE_2_BASE(x, y) \
  SWIZZLE_2_BASE(r, g)

namespace linalg {
  template <typename T, std::size_t N>
  struct vec;
  template <typename T, std::size_t N>
  struct swizzle;

  template <typename T>
  struct swizzle<T, 2> {
    typedef T& value_type;
    typedef std::size_t size_type;

    swizzle(const swizzle<T, 2>& copy) : x(copy.x), y(copy.y) {}
    swizzle(value_type& x, value_type& y) : x(x), y(y) {}
    static constexpr size_type length() { return 2; }
    static constexpr size_type size() { return 2; }

    template <typename U,
              typename = std::enable_if_t<std::is_convertible<U, T>::value>>
    swizzle<T, 2>& operator=(const U& v) {
      x = static_cast<T>(v);
      y = static_cast<T>(v);
      return *this;
    }
    swizzle<T, 2>& operator=(const T& v) {
      x = v;
      y = v;
      return *this;
    }
    template <
        typename U, std::size_t N,
        typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
    swizzle<T, 2>& operator=(const vec<U, N>& v) {
      x = static_cast<T>(v.x);
      y = static_cast<T>(v.y);
      return *this;
    }
    template <std::size_t N, typename = std::enable_if_t<N >= 2>>
    swizzle<T, 2>& operator=(const vec<T, N>& v) {
      x = v.x;
      y = v.y;
      return *this;
    }
    swizzle<T, 2>& operator=(const vec<T, 2>& v) {
      x = v.x;
      y = v.y;
      return *this;
    }
    template <
        typename U, std::size_t N,
        typename = std::enable_if_t<std::is_convertible<U, T>::value && N >= 2>>
    swizzle<T, 2>& operator=(const swizzle<U, N>& v) {
      x = static_cast<T>(v.x);
      y = static_cast<T>(v.y);
      return *this;
    }
    template <std::size_t N, typename = std::enable_if_t<N >= 2>>
    swizzle<T, 2>& operator=(const swizzle<T, N>& v) {
      x = v.x;
      y = v.y;
      return *this;
    }
    swizzle<T, 2>& operator=(const swizzle<T, 2>& v) {
      x = v.x;
      y = v.y;
      return *this;
    }

    value_type& operator[](const size_type& i) {
      switch (i) {
        case 0:
          return x;
        case 1:
          return y;
        default:
          throw std::out_of_range(
              "swizzle<T,2>::operator[] : index is out of range");
      }
    }
    value_type operator[](const size_type& i) const {
      switch (i) {
        case 0:
          return x;
        case 1:
          return y;
        default:
          throw std::out_of_range(
              "swizzle<T,2>::operator[] : index is out of range");
      }
    }

    template <
        typename U, std::size_t N,
        typename = std::enable_if_t<std::is_convertible<T, U>::value && N >= 2>>
    operator vec<U, N>() const {
      return {static_cast<U>(x), static_cast<U>(y)};
    }

    value_type x, y;
  };
#ifdef LINALG_OSTREAM_OPERATOR
  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const swizzle<T, 2>& rhs) {
    return out << '<' << rhs.x << ',' << rhs.y << '>';
  }
#endif
}  // namespace linalg

#endif  // LINALG_SWIZZLE_FUNCTIONS_H_
