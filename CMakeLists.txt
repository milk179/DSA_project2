cmake_minimum_required(VERSION 3.14)
project(SortComparator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(sort_comparator
    main.cpp
    sorter.cpp
    dataloader.cpp
    comparator.cpp
)

target_include_directories(sort_comparator PRIVATE ${CMAKE_SOURCE_DIR})
