# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(
  linalg
  VERSION 0.0.11
  LANGUAGES CXX)

if(NOT DEFINED LINALG_MASTER_PROJECT)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(LINALG_MASTER_PROJECT TRUE)
  else()
    set(LINALG_MASTER_PROJECT FALSE)
  endif()
endif()
include(GNUInstallDirs)

# ##############################################################################
# OPTIONS
# ##############################################################################
option(LINALG_BUILD_SHARED "Build shared library" OFF)
option(LINALG_BUILD_TESTS "Build tests" ${LINALG_MASTER_PROJECT})
option(LINALG_BUILD_TESTS_HO "Build tests using the header only version"
       ${LINALG_MASTER_PROJECT})
option(LINALG_INSTALL "Generate the install target" ${LINALG_MASTER_PROJECT})
option(STATIC_ANALYSIS "Enable static analysis" FALSE)

# ##############################################################################
# COMPILER
# ##############################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ##############################################################################
# SOURCE
# ##############################################################################
set(SOURCE src/linalg.cpp)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h")
set(LINALG_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(LINALG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ##############################################################################
# BUILD TYPE
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Choose the type of build" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
  if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
              ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
  endif()
endif()

# ##############################################################################
# STATIC ANALYSIS
# ##############################################################################
if(STATIC_ANALYSIS OR CMAKE_BUILD_TYPE STREQUAL "Release")
  find_program(CLANG_TIDY "clang-tidy")
  if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
  endif()
  find_program(CPPCHECK "cppcheck")
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK})
    list(APPEND CMAKE_CXX_CPPCHECK "--force")
  endif()
  find_program(CPPLINT "cpplint")
  if(CPPLINT)
    set(CMAKE_CXX_CPPLINT ${CPPLINT})
  endif()
endif()

# ##############################################################################
# TARGET LIBRARY
# ##############################################################################
if(LINALG_BUILD_SHARED)
  add_library(linalg SHARED ${SOURCE})
else()
  add_library(linalg STATIC ${SOURCE})
endif()
add_library(${PROJECT_NAME}::linalg ALIAS linalg)
target_include_directories(
  linalg PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_compile_options(linalg PUBLIC -DLINALG_COMPILED_LIB)
target_compile_options(linalg
                       PRIVATE $<$<CONFIG:Debug>:-O0>$<$<CONFIG:Release>:-O3>)
target_compile_options(
  linalg
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall
    -Wextra
    -Wconversion
    -pedantic
    -Wfatal-errors>
    $<$<CXX_COMPILER_ID:MSVC>:/W4
    /WX>)
target_compile_definitions(linalg PUBLIC
                           $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>)
set_target_properties(linalg PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION
                                        ${PROJECT_VERSION_MAJOR})

# ##############################################################################
# TARGET HEADER ONLY LIBRARY
# ##############################################################################
add_library(linalg_header_only INTERFACE)
add_library(${PROJECT_NAME}::header_only ALIAS linalg_header_only)
target_include_directories(
  linalg_header_only
  INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# ##############################################################################
# TESTING
# ##############################################################################
if(LINALG_BUILD_TESTS OR LINALG_BUILD_TESTS_HO)
  message(STATUS "Generating tests")
  enable_testing()
  add_subdirectory(tests)
endif()

# ##############################################################################
# INSTALL
# ##############################################################################
if(LINALG_INSTALL)
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
          DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(
    TARGETS linalg linalg_header_only
    EXPORT linalg
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()

# ##############################################################################
# PACKAGING
# ##############################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CPACK_GENERATOR "TGZ;ZIP")
  set(CPACK_PACKAGE_VENDOR "LuxAter")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()
