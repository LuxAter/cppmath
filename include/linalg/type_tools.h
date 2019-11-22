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

#ifndef LINALG_TYPE_TOOLS_H_
#define LINALG_TYPE_TOOLS_H_

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include "export.h"

namespace linalg {
  namespace sfinae {

    template <class T>
    EXPORTED constexpr auto type_name() {
      std::string_view name, prefix, suffix;
#ifdef __clang__
      name = __PRETTY_FUNCTION__;
      prefix = "auto linalg::sfinae::type_name() [T = ";
      suffix = "]";
#elif defined(__GNUC__)
      name = __PRETTY_FUNCTION__;
      prefix = "constexpr auto linalg::sfinae::type_name() [with T = ";
      suffix = "]";
#elif defined(_MSC_VER)
      name = __FUNCSIG__;
      prefix = "auto __cdecl linalg::sfinae::type_name<";
      suffix = ">(void)";
#endif
      name.remove_prefix(prefix.size());
      name.remove_suffix(suffix.size());
      return name;
    }

    template <class T, class S>
    struct EXPORTED has_eq_impl {
      template <class TT, class SS>
      constexpr static auto test(TT*)
          -> decltype(std::declval<TT>() == std::declval<SS>());
      template <typename, typename>
      constexpr static auto test(...) -> std::false_type;

      using type = typename std::is_same<bool, decltype(test<T, S>(0))>::type;
    };

    template <class T, class S = T>
    struct has_eq : has_eq_impl<T, S>::type {};

    template <class T, class S>
    struct has_neq_impl {
      template <class TT, class SS>
      static auto test(TT*)
          -> decltype(std::declval<TT>() != std::declval<SS>());
      template <typename, typename>
      static auto test(...) -> std::false_type;

      using type = typename std::is_same<bool, decltype(test<T, S>(0))>::type;
    };

    template <class T, class S = T>
    struct has_neq : has_neq_impl<T, S>::type {};

    template <class T, class S>
    struct has_lt_impl {
      template <class TT, class SS>
      static auto test(TT*)
          -> decltype(std::declval<TT>() < std::declval<SS>());
      template <typename, typename>
      static auto test(...) -> std::false_type;

      using type = typename std::is_same<bool, decltype(test<T, S>(0))>::type;
    };

    template <class T, class S = T>
    struct has_lt : has_lt_impl<T, S>::type {};

    template <class T, class S>
    struct has_gt_impl {
      template <class TT, class SS>
      static auto test(TT*)
          -> decltype(std::declval<TT>() > std::declval<SS>());
      template <typename, typename>
      static auto test(...) -> std::false_type;

      using type = typename std::is_same<bool, decltype(test<T, S>(0))>::type;
    };

    template <class T, class S = T>
    struct has_gt : has_gt_impl<T, S>::type {};

    template <class T, class S>
    struct has_leq_impl {
      template <class TT, class SS>
      static auto test(TT*)
          -> decltype(std::declval<TT>() <= std::declval<SS>());
      template <typename, typename>
      static auto test(...) -> std::false_type;

      using type = typename std::is_same<bool, decltype(test<T, S>(0))>::type;
    };

    template <class T, class S = T>
    struct has_leq : has_leq_impl<T, S>::type {};

    template <class T, class S>
    struct has_geq_impl {
      template <class TT, class SS>
      static auto test(TT*)
          -> decltype(std::declval<TT>() >= std::declval<SS>());
      template <typename, typename>
      static auto test(...) -> std::false_type;

      using type = typename std::is_same<bool, decltype(test<T, S>(0))>::type;
    };

    template <class T, class S = T>
    struct has_geq : has_geq_impl<T, S>::type {};

  }  // namespace sfinae
}  // namespace linalg

#endif  // LINALG_TYPE_TOOLS_H_
