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

if(LINALG_TEST_COVERAGE)
  if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
     OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
    find_program(GCOV_TOOL "llvm-cov")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    find_program(GCOV_TOOL "gcov")
  endif()
  find_program(GCOVR_PATH gcovr)

  if(NOT GCOV_TOOL)
    message(WARNING "gcov/llvm-cov not found!")
  endif()
  if(NOT GCOVR_PATH)
    message(WARNING "gcovr not found!")
  endif()

  if(NOT GCOV_TOOL OR NOT GCOVR_PATH)
    add_custom_target(coverage linalg-tests ${ARGV3}
                      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  else()
    set(CMAKE_CXX_FLAGS_DEBUG
        "-g -O0 --std=c++17 --coverage"
        CACHE STRING "Flags used by the C++ compiler during coverage builds."
              FORCE)
    set(CMAKE_C_FLAGS_DEBUG
        "-g -O0 -fprofile-arcs -ftest-coverage"
        CACHE STRING "Flags used by the C compiler during coverage builds."
              FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG
        "--std=c++17 --coverage"
        CACHE STRING "Flags used for linking binaries during coverage builds."
              FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG
        ""
        CACHE
          STRING
          "Flags used by the shared libraries linker during coverage builds."
          FORCE)
    mark_as_advanced(
      CMAKE_CXX_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG CMAKE_EXE_LINKER_FLAGS_DEBUG
      CMAKE_SHARED_LINKER_FLAGS_DEBUG)
    add_custom_target(
      coverage linalg-tests ${ARGV3}
      COMMAND mkdir -p coverage
      COMMAND
        cd coverage && ${GCOVR_PATH} --gcov-executable ${GCOV_TOOL} -r
        ${CMAKE_CURRENT_SOURCE_DIR} -e '.*/tests/.*' -e '.*/external/.*' -s
        --html --html-details -o index.html
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()
endif()
