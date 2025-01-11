
cmake_minimum_required(VERSION 3.14)
project(app VERSION)

include(FetchContent)

# Fetch ncurses
FetchContent_Declare(
  ncurses
  GIT_REPOSITORY https://github.com/mirror/ncurses.git
  GIT_TAG master
)
FetchContent_MakeAvailable(ncurses)

add_executable(${PROJECT_NAME} ncur.cpp)

# Link library
target_link_libraries(${PROJECT_NAME} PRIVATE ncurses)
