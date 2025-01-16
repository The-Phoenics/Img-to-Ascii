
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

file(GLOB SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link library
target_link_libraries(${PROJECT_NAME} PRIVATE ncurses)
