cmake_minimum_required(VERSION 3.20)

project(src
    VERSION 0.1.0
    DESCRIPTION "A source retrieval tool"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(src
    src/main.cpp
    src/app.cpp
    src/command.cpp
    src/git.cpp
)
target_include_directories(src
    PRIVATE
        include
)

if(MSVC)
    target_compile_options(src PRIVATE /W4)
else()
    target_compile_options(src PRIVATE -Wall -Wextra -Wpedantic)
endif()