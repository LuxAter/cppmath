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

#define SWIZZLE_2_BASE(a, b)                           \
  inline vec<value_type&, 2> a##b() { return {a, b}; } \
  inline vec<const value_type&, 2> a##b() const { return {a, b}; }
#define SWIZZLE_3_BASE(a, b, c)                              \
  inline vec<value_type&, 3> a##b##c() { return {a, b, c}; } \
  inline vec<const value_type&, 3> a##b##c() const { return {a, b, c}; }
#define SWIZZLE_4_BASE(a, b, c, d)                                 \
  inline vec<value_type&, 4> a##b##c##d() { return {a, b, c, d}; } \
  inline vec<const value_type&, 4> a##b##c##d() const { return {a, b, c, d}; }

#define SWIZZLE_12_BASE(a) SWIZZLE_2_BASE(a, a)

#define SWIZZLE_13_BASE(a) SWIZZLE_3_BASE(a, a, a)

#define SWIZZLE_14_BASE(a) SWIZZLE_4_BASE(a, a, a, a)

#define SWIZZLE_22_BASE(a, b) \
  SWIZZLE_2_BASE(a, b)        \
  SWIZZLE_2_BASE(b, a)

#define SWIZZLE_23_BASE(a, b) \
  SWIZZLE_3_BASE(a, a, b)     \
  SWIZZLE_3_BASE(a, b, a)     \
  SWIZZLE_3_BASE(a, b, b)     \
  SWIZZLE_3_BASE(b, a, a)     \
  SWIZZLE_3_BASE(b, a, b)     \
  SWIZZLE_3_BASE(b, b, a)

#define SWIZZLE_24_BASE(a, b) \
  SWIZZLE_4_BASE(a, a, a, b)  \
  SWIZZLE_4_BASE(a, a, b, a)  \
  SWIZZLE_4_BASE(a, a, b, b)  \
  SWIZZLE_4_BASE(a, b, a, a)  \
  SWIZZLE_4_BASE(a, b, a, b)  \
  SWIZZLE_4_BASE(a, b, b, a)  \
  SWIZZLE_4_BASE(a, b, b, b)  \
  SWIZZLE_4_BASE(b, a, a, a)  \
  SWIZZLE_4_BASE(b, a, a, b)  \
  SWIZZLE_4_BASE(b, a, b, a)  \
  SWIZZLE_4_BASE(b, a, b, b)  \
  SWIZZLE_4_BASE(b, b, a, a)  \
  SWIZZLE_4_BASE(b, b, a, b)  \
  SWIZZLE_4_BASE(b, b, b, a)

#define SWIZZLE_33_BASE(a, b, c) \
  SWIZZLE_3_BASE(a, b, c)        \
  SWIZZLE_3_BASE(a, c, b)        \
  SWIZZLE_3_BASE(b, a, c)        \
  SWIZZLE_3_BASE(b, c, a)        \
  SWIZZLE_3_BASE(c, b, a)        \
  SWIZZLE_3_BASE(c, a, b)

#define SWIZZLE_34_BASE(a, b, c) \
  SWIZZLE_4_BASE(a, a, b, c)     \
  SWIZZLE_4_BASE(a, a, c, b)     \
  SWIZZLE_4_BASE(a, b, a, c)     \
  SWIZZLE_4_BASE(a, b, b, c)     \
  SWIZZLE_4_BASE(a, b, c, a)     \
  SWIZZLE_4_BASE(a, b, c, b)     \
  SWIZZLE_4_BASE(a, b, c, c)     \
  SWIZZLE_4_BASE(a, c, a, b)     \
  SWIZZLE_4_BASE(a, c, b, a)     \
  SWIZZLE_4_BASE(a, c, b, b)     \
  SWIZZLE_4_BASE(a, c, b, c)     \
  SWIZZLE_4_BASE(a, c, c, b)     \
  SWIZZLE_4_BASE(b, a, a, c)     \
  SWIZZLE_4_BASE(b, a, b, c)     \
  SWIZZLE_4_BASE(b, a, c, a)     \
  SWIZZLE_4_BASE(b, a, c, b)     \
  SWIZZLE_4_BASE(b, a, c, c)     \
  SWIZZLE_4_BASE(b, b, a, c)     \
  SWIZZLE_4_BASE(b, b, c, a)     \
  SWIZZLE_4_BASE(b, c, a, a)     \
  SWIZZLE_4_BASE(b, c, a, b)     \
  SWIZZLE_4_BASE(b, c, a, c)     \
  SWIZZLE_4_BASE(b, c, b, a)     \
  SWIZZLE_4_BASE(b, c, c, a)     \
  SWIZZLE_4_BASE(c, a, a, b)     \
  SWIZZLE_4_BASE(c, a, b, a)     \
  SWIZZLE_4_BASE(c, a, b, b)     \
  SWIZZLE_4_BASE(c, a, b, c)     \
  SWIZZLE_4_BASE(c, a, c, b)     \
  SWIZZLE_4_BASE(c, b, a, a)     \
  SWIZZLE_4_BASE(c, b, a, b)     \
  SWIZZLE_4_BASE(c, b, a, c)     \
  SWIZZLE_4_BASE(c, b, b, a)     \
  SWIZZLE_4_BASE(c, b, c, a)     \
  SWIZZLE_4_BASE(c, c, a, b)     \
  SWIZZLE_4_BASE(c, c, b, a)

#define SWIZZLE_44_BASE()    \
  SWIZZLE_4_BASE(a, b, c, d) \
  SWIZZLE_4_BASE(a, b, d, c) \
  SWIZZLE_4_BASE(a, c, b, d) \
  SWIZZLE_4_BASE(a, c, d, b) \
  SWIZZLE_4_BASE(a, d, b, c) \
  SWIZZLE_4_BASE(a, d, c, b) \
  SWIZZLE_4_BASE(b, a, c, d) \
  SWIZZLE_4_BASE(b, a, d, c) \
  SWIZZLE_4_BASE(b, c, a, d) \
  SWIZZLE_4_BASE(b, c, d, a) \
  SWIZZLE_4_BASE(b, d, a, c) \
  SWIZZLE_4_BASE(b, d, c, a) \
  SWIZZLE_4_BASE(c, b, a, d) \
  SWIZZLE_4_BASE(c, b, d, a) \
  SWIZZLE_4_BASE(c, a, b, d) \
  SWIZZLE_4_BASE(c, a, d, b) \
  SWIZZLE_4_BASE(c, d, b, a) \
  SWIZZLE_4_BASE(c, d, a, b) \
  SWIZZLE_4_BASE(d, b, c, a) \
  SWIZZLE_4_BASE(d, b, a, c) \
  SWIZZLE_4_BASE(d, c, b, a) \
  SWIZZLE_4_BASE(d, c, a, b) \
  SWIZZLE_4_BASE(d, a, b, c) \
  SWIZZLE_4_BASE(d, a, c, b)

#define SWIZZLE_2()     \
  SWIZZLE_22_BASE(x, y) \
  SWIZZLE_23_BASE(x, y) \
  SWIZZLE_24_BASE(x, y)

#define SWIZZLE_3()        \
  SWIZZLE_22_BASE(x, y)    \
  SWIZZLE_23_BASE(x, y)    \
  SWIZZLE_24_BASE(x, y)    \
  SWIZZLE_22_BASE(x, z)    \
  SWIZZLE_23_BASE(x, z)    \
  SWIZZLE_24_BASE(x, z)    \
  SWIZZLE_22_BASE(y, z)    \
  SWIZZLE_23_BASE(y, z)    \
  SWIZZLE_24_BASE(y, z)    \
  SWIZZLE_33_BASE(x, y, z) \
  SWIZZLE_34_BASE(x, y, z)

#define SWIZZLE_4()        \
  SWIZZLE_22_BASE(x, y)    \
  SWIZZLE_23_BASE(x, y)    \
  SWIZZLE_24_BASE(x, y)    \
  SWIZZLE_22_BASE(x, z)    \
  SWIZZLE_23_BASE(x, z)    \
  SWIZZLE_24_BASE(x, z)    \
  SWIZZLE_22_BASE(x, w)    \
  SWIZZLE_23_BASE(x, w)    \
  SWIZZLE_24_BASE(x, w)    \
  SWIZZLE_22_BASE(y, z)    \
  SWIZZLE_23_BASE(y, z)    \
  SWIZZLE_24_BASE(y, z)    \
  SWIZZLE_22_BASE(y, w)    \
  SWIZZLE_23_BASE(y, w)    \
  SWIZZLE_24_BASE(y, w)    \
  SWIZZLE_22_BASE(z, w)    \
  SWIZZLE_23_BASE(z, w)    \
  SWIZZLE_24_BASE(z, w)    \
  SWIZZLE_33_BASE(x, y, z) \
  SWIZZLE_33_BASE(x, y, w) \
  SWIZZLE_33_BASE(x, z, w) \
  SWIZZLE_33_BASE(y, z, w) \
  SWIZZLE_34_BASE(x, y, z) \
  SWIZZLE_34_BASE(x, y, w) \
  SWIZZLE_34_BASE(x, z, w) \
  SWIZZLE_34_BASE(y, z, w) \
  SWIZZLE_44_BASE(x, y, z, w)

#endif  // LINALG_SWIZZLE_FUNCTIONS_H_
