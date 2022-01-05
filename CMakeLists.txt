cmake_minimum_required(VERSION 3.10)

project(game_engine)

add_executable( game_engine 
  main.c
  shader.c
  file_utility.c
  model.c
  engine.c
  msqglm/vec.c
  msqglm/mat.c
  msqutils/msq.c
)

#required by glfw
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories($(GLFW_INCLUDE_DIRS))
target_link_libraries(game_engine ${GLFW_LIBRARIES})

#required by glew
target_link_libraries(game_engine GLEW GL m)
#find_package(GLEW REQUIRED)
#include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARIES})

link_directories(${CMAKE_SOURCE_DIR}/msqglm)
link_directories(${CMAKE_SOURCE_DIR}/msqutils)
link_directories(${CMAKE_SOURCE_DIR}/stb)

add_custom_command(TARGET game_engine PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:game_engine>/res)
