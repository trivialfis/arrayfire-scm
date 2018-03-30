set(SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/arrayfire_scm.c
  ${CMAKE_CURRENT_SOURCE_DIR}/linear_algebra.c
  ${CMAKE_CURRENT_SOURCE_DIR}/construction.c
  ${CMAKE_CURRENT_SOURCE_DIR}/mathematic.c
  ${CMAKE_CURRENT_SOURCE_DIR}/io.c
  ${CMAKE_CURRENT_SOURCE_DIR}/index.c
  ${CMAKE_CURRENT_SOURCE_DIR}/array.c
  ${CMAKE_CURRENT_SOURCE_DIR}/statistics.c)

add_library(afs SHARED ${SRCS})
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUILE REQUIRED "guile-2.2")
include_directories(${GUILE_INCLUDE_DIRS})

find_package(ArrayFire)
include_directories(${ArrayFire_INCLUDE_DIRS})

target_link_libraries(afs ${GUILE_LIBRARIES})
target_link_libraries(afs ${ArrayFire_LIBRARIES})

include(GNUInstallDirs)

install(TARGETS afs LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
