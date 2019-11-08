# Copyright(c) 2019 cppmath authors
# Distributed under the MIT License (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.2)

#---------------------------------------------------------------------------------------
# Start cppmath project
#---------------------------------------------------------------------------------------
include(GenerateExportHeader)
include(GNUInstallDirs)
include(cmake/utils.cmake)
include(cmake/ide.cmake)

#---------------------------------------------------------------------------------------
# Set default build to release
#---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

project(cppmath VERSION 0.0.0 LANGUAGES CXX)
message(STATUS "Build cppmath: ${PROJECT_VERSION}")

#---------------------------------------------------------------------------------------
# Compiler config
#---------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_program(CLANG_TIDY_EXEC NAMES clang-tidy)
find_program(CPPCHECK_EXEC NAMES cppcheck)
if(CLANG_TIDY_EXEC)
  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXEC})
endif()
if(CPPCHECK_EXEC)
  set(CMAKE_CXX_CPPCHECK ${CPPCHECK_EXEC})
endif()


#---------------------------------------------------------------------------------------
# Set CPPMATH_MASTER_PROJECT to ON if we are building cppmath
#---------------------------------------------------------------------------------------
# Check if cppmath is being used directly or via add_subdirectory, but allow overriding
if (NOT DEFINED CPPMATH_MASTER_PROJECT)
  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CPPMATH_MASTER_PROJECT ON)
  else()
    set(CPPMATH_MASTER_PROJECT OFF)
  endif()
endif ()

# build shared option
if(NOT WIN32)
  option(CPPMATH_BUILD_SHARED "Build shared library" OFF)
endif()

# example options
option(CPPMATH_BUILD_EXAMPLE "Build example" ${CPPMATH_MASTER_PROJECT})
option(CPPMATH_BUILD_EXAMPLE_HO "Build header only example" OFF)

# testing options
option(CPPMATH_BUILD_TESTS "Build tests" ${CPPMATH_MASTER_PROJECT})
option(CPPMATH_BUILD_TESTS_HO "Build tests using the header only version" OFF)

# sanitizer options
option(CPPMATH_SANITIZE_ADDRESS "Enable address sanitizer in tests" OFF)

# install options
option(CPPMATH_INSTALL "Generate the install target" ${CPPMATH_MASTER_PROJECT})

if(WIN32)
  option(CPPMATH_WCHAR_SUPPORT "Support wchar api" OFF)
  option(CPPMATH_WCHAR_FILENAMES "Support wchar filenames" OFF)
endif()

option(CPPMATH_NO_EXCEPTIONS "Compile with -fno-exceptions. Call abort() on any cppmath exceptions" OFF)


message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
find_package(Threads REQUIRED)

#---------------------------------------------------------------------------------------
# Static/Shared library (shared not supported in windows yet)
#---------------------------------------------------------------------------------------
set(CPPMATH_SRCS
  src/cppmath.cpp)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/cppmath/version.h.in" 
               "${CMAKE_CURRENT_SOURCE_DIR}/include/cppmath/version.h")

if (CPPMATH_BUILD_SHARED)
  if(WIN32)
    message(FATAL_ERROR "cppmath shared lib is not yet supported under windows")
  endif()
  add_library(cppmath SHARED ${CPPMATH_SRCS} ${CPPMATH_ALL_HEADERS})
else()
  add_library(cppmath STATIC ${CPPMATH_SRCS} ${CPPMATH_ALL_HEADERS})
endif()

add_library(cppmath::cppmath ALIAS cppmath)

target_compile_definitions(cppmath PUBLIC CPPMATH_COMPILED_LIB)
target_include_directories(cppmath PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(cppmath PUBLIC Threads::Threads)
generate_export_header(cppmath)
cppmath_enable_warnings(cppmath)

set_target_properties(cppmath PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(cppmath PROPERTIES DEBUG_POSTFIX d)

#---------------------------------------------------------------------------------------
# Header only version
#---------------------------------------------------------------------------------------
add_library(cppmath_header_only INTERFACE)
add_library(cppmath::cppmath_header_only ALIAS cppmath_header_only)

target_include_directories(cppmath_header_only INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(cppmath_header_only INTERFACE Threads::Threads)

#---------------------------------------------------------------------------------------
# Build binaries
#---------------------------------------------------------------------------------------
if(CPPMATH_BUILD_EXAMPLE OR CPPMATH_BUILD_EXAMPLE_HO)
  message(STATUS "Generating examples")
  add_subdirectory(example)
endif()

if(CPPMATH_BUILD_TESTS OR CPPMATH_BUILD_TESTS_HO)
  message(STATUS "Generating tests")
  enable_testing()
  add_subdirectory(tests)
endif()

#---------------------------------------------------------------------------------------
# Install
#---------------------------------------------------------------------------------------
if (CPPMATH_INSTALL)
  message(STATUS "Generating install")
  set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/cmake/cppmathConfig.cmake.in")
  set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/cppmathConfig.cmake")
  set(config_targets_file "cppmathConfigTargets.cmake")
  set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/cppmathConfigVersion.cmake")
  set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/cppmath")
  set(pkgconfig_install_dir "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  set(pkg_config "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc")

  #---------------------------------------------------------------------------------------
  # Include files
  #---------------------------------------------------------------------------------------
  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(TARGETS cppmath cppmath_header_only EXPORT cppmath DESTINATION "${CMAKE_INSTALL_LIBDIR}")

  #---------------------------------------------------------------------------------------
  # Install pkg-config file
  #---------------------------------------------------------------------------------------
  get_target_property(PKG_CONFIG_DEFINES cppmath INTERFACE_COMPILE_DEFINITIONS)
  string(REPLACE ";" " -D" PKG_CONFIG_DEFINES "${PKG_CONFIG_DEFINES}")
  string(CONCAT PKG_CONFIG_DEFINES "-D" "${PKG_CONFIG_DEFINES}")
  configure_file("cmake/${PROJECT_NAME}.pc.in" "${pkg_config}" @ONLY)
  install(FILES "${pkg_config}" DESTINATION "${pkgconfig_install_dir}")

  #---------------------------------------------------------------------------------------
  # Install CMake config files
  #---------------------------------------------------------------------------------------
  install(EXPORT cppmath
    DESTINATION ${export_dest_dir}
    NAMESPACE cppmath::
    FILE ${config_targets_file})

  include(CMakePackageConfigHelpers)
  configure_file("${project_config_in}" "${project_config_out}" @ONLY)

  write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
  install(FILES
    "${project_config_out}"
    "${version_config_file}" DESTINATION "${export_dest_dir}")

  #---------------------------------------------------------------------------------------
  # Support creation of installable packages
  #---------------------------------------------------------------------------------------
  include(cmake/cppmathCPack.cmake)

endif ()

