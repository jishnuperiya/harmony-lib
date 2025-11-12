#********* Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
#**
#**
#**  Version : $Header:$
#**
#**
#**  Purpose : CMake build script for the jishnu project.
#**
#**
#**  See Also: https://cmake.org/cmake/help/latest/
#**            for more on the CMake language.
#**
#**            https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
#**            for more on specifying the C++ standard.
#**
#**            https://stackoverflow.com/a/59108287
#**            for more on specifying compiler options.
#**
#**
#*****************************************************************************

cmake_minimum_required(VERSION 3.20.2)

project(jishnu
  VERSION       0.1.0.1
  HOMEPAGE_URL  "https://github.com/jishnuperiya/repo-no-name")

#*****************************************************************************

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#find_package(Doxygen    1.9.8  REQUIRED)
find_package(DocTest    2.4.11 REQUIRED)
find_package(RapidCheck        REQUIRED)

set(CMAKE_CXX_STANDARD          23 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS        OFF)

enable_testing()

add_compile_options(-Wall)

#*****************************************************************************

add_library(jishnu-lib STATIC
  src/example.cpp
  src/complex.cpp
  src/string.cpp
  src/pitch.cpp
  src/frequency.cpp
  src/note.cpp
  src/chord.cpp
  src/progression.cpp)

target_link_libraries(jishnu-lib)

target_include_directories(jishnu-lib PUBLIC src)

set_target_properties(jishnu-lib PROPERTIES OUTPUT_NAME jishnu)

#*****************************************************************************

add_executable(jishnu
  src/jishnu.cpp )

target_link_libraries(jishnu
  jishnu-lib)

  #*****************************************************************************

add_executable(jishnu-test
  test/main.cpp
  test/example.cpp
  test/test_pitch.cpp
  test/test_frequency.cpp
  test/test_note.cpp
  test/test_voicing.cpp)



# --------------------------------------------------------------------
# Workaround for RapidCheck missing <cstdint> include (MSVC + GCC/Clang)
# --------------------------------------------------------------------
if(TARGET rapidcheck)
  if(MSVC)
    target_compile_options(rapidcheck PRIVATE /FIcstdint)
  else()
    target_compile_options(rapidcheck PRIVATE -include cstdint)
  endif()
endif()


target_link_libraries(jishnu-test
  jishnu-lib
  rapidcheck
  doctest::doctest)

#*****************************************************************************

add_test(NAME jishnu.example COMMAND jishnu-test)

#*****************************************************************************
