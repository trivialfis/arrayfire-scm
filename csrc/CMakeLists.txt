set(SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/arrayfire_scm.c
  ${CMAKE_CURRENT_SOURCE_DIR}/linear_algebra.c
  ${CMAKE_CURRENT_SOURCE_DIR}/construction.c
  ${CMAKE_CURRENT_SOURCE_DIR}/mathematic.c
  ${CMAKE_CURRENT_SOURCE_DIR}/io.c)

add_library(arrayfire-scm SHARED ${SRCS})
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUILE "guile-2.2")
include_directories(${GUILE_INCLUDE_DIRS})

find_package(ArrayFire)
include_directories(${ArrayFire_INCLUDE_DIRS})

target_link_libraries(arrayfire-scm ${GUILE_LIBRARIES})
target_link_libraries(arrayfire-scm ${ArrayFire_LIBRARIES})
