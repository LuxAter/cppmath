#ifndef TEST_TIMER_H_
#define TEST_TIMER_H_

#include <chrono>

template <std::size_t N, typename _F, typename... _ARGS>
std::chrono::microseconds time_function(_F&& func, _ARGS&&... args) {
  auto start = std::chrono::high_resolution_clock::now();
  for (std::size_t i = 0; i < N; ++i) {
    func(args...);
  }
  return std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::now() - start);
}

#endif  // TEST_TIMER_H_
