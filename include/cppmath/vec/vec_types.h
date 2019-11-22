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

#ifndef CPPMATH_VEC_TYPES_H_
#define CPPMATH_VEC_TYPES_H_

#include <cstdlib>

#include "vec_base.h"

namespace math {
  template <std::size_t N>
  using bvec = vec<bool, N>;
  template <std::size_t N>
  using ivec = vec<int, N>;
  template <std::size_t N>
  using uvec = vec<unsigned, N>;
  template <std::size_t N>
  using fvec = vec<float, N>;
  template <std::size_t N>
  using dvec = vec<double, N>;

  typedef vec<bool, 1> bvec1;
  typedef vec<bool, 2> bvec2;
  typedef vec<bool, 3> bvec3;
  typedef vec<bool, 4> bvec4;
  typedef vec<int, 1> ivec1;
  typedef vec<int, 2> ivec2;
  typedef vec<int, 3> ivec3;
  typedef vec<int, 4> ivec4;
  typedef vec<unsigned, 1> uvec1;
  typedef vec<unsigned, 2> uvec2;
  typedef vec<unsigned, 3> uvec3;
  typedef vec<unsigned, 4> uvec4;
  typedef vec<float, 1> fvec1;
  typedef vec<float, 2> fvec2;
  typedef vec<float, 3> fvec3;
  typedef vec<float, 4> fvec4;
  typedef vec<double, 1> dvec1;
  typedef vec<double, 2> dvec2;
  typedef vec<double, 3> dvec3;
  typedef vec<double, 4> dvec4;
}  // namespace math

#endif  // CPPMATH_VEC_TYPES_H_
