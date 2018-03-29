project(arrayfire-scm)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/csrc)

install(FILES
  arrayfire.scm
  DESTINATION "share/guile/site/2.2")
install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/arrayfire/library.scm
  ${CMAKE_CURRENT_SOURCE_DIR}/arrayfire/ling.scm
  DESTINATION "share/guile/site/2.2/arrayfire")
