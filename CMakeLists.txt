cmake_minimum_required(VERSION 3.20)

project(src
    VERSION 0.1.0
    DESCRIPTION "A source retrieval tool"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(src
    src/main.cpp
    src/app.cpp
    src/command.cpp
    src/paths.cpp
    src/package_manifest.cpp
    src/manifest_parser.cpp
    src/string_utils.cpp
    src/registry.cpp
    src/registry_manager.cpp
    src/downloader.cpp
    src/package_downloader.cpp
    src/download_progress.cpp
    src/task_progress.cpp
    src/extractor.cpp
    third_party/miniz/miniz.c
    src/cleanup.cpp

    include/app.hpp
    include/command.hpp
    include/paths.hpp
    include/package_manifest.hpp
    include/manifest_parser.hpp

    
)

target_include_directories(src PRIVATE
    include
    third_party/miniz
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)

target_link_libraries(src PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)

if(MSVC)
    target_compile_options(src PRIVATE /W4)
else()
    target_compile_options(src PRIVATE -Wall -Wextra -Wpedantic)
endif()