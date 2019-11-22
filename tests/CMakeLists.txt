project(tests LANGUAGES CXX)
set(TESTS_SOURCES main.cpp type_tool.cpp)

enable_testing()

function(prepare_test test_target lib)
  add_executable(${test_target} ${TESTS_SOURCES})
  target_compile_options(
    ${test_target}
    PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall
      -Wextra
      -Wconversion
      -pedantic
      -Wfatal-errors>
      $<$<CXX_COMPILER_ID:MSVC>:/W4
      /WX>)
  target_link_libraries(${test_target} PRIVATE ${lib})
  add_test(NAME ${test_target} COMMAND ${test_target})
endfunction()

if(LINALG_BUILD_TESTS)
  prepare_test(linalg-tests linalg::linalg)
endif()

if(LINALG_BUILD_TESTS)
  prepare_test(linalg-tests-ho linalg::header_only)
endif()
