cmake_minimum_required(VERSION 3.12)

project(FolderUtil VERSION 1.0 LANGUAGES CXX)

find_package(Boost 1.81 COMPONENTS program_options REQUIRED)

add_executable(FolderUtil 
    src/main.cpp
    src/random/random.cpp
    src/folder_spam/folder_spam.cpp
    src/print/print.cpp
)

target_link_libraries(FolderUtil PRIVATE
    ${Boost_LIBRARIES})

target_include_directories(FolderUtil PRIVATE
    src/random
    src/folder_spam
    src/print
    src
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)