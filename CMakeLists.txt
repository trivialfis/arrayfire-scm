project(arrayfire-scm)
cmake_minimum_required(VERSION 3.0)

set(SRCS
  arrayfire_scm.c
  linear_algebra.c
  construction.c
  mathematic.c)

add_library(arrayfire-scm SHARED ${SRCS})
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUILE "guile-2.2")
include_directories(${GUILE_INCLUDE_DIRS})

find_package(ArrayFire)
include_directories(${ArrayFire_INCLUDE_DIRS})

target_link_libraries(arrayfire-scm ${GUILE_LIBRARIES})
target_link_libraries(arrayfire-scm ${ArrayFire_LIBRARIES})
