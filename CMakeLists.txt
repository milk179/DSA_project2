cmake_minimum_required(VERSION 3.14)
project(SortComparator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
include(FetchContent)

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

FetchContent_Declare(
    Catch2
    URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.8.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    TLS_VERIFY FALSE
)

FetchContent_MakeAvailable(Catch2)

add_executable(sort_comparator_tests
    test.cpp
    sorter.cpp
    dataloader.cpp
    comparator.cpp
)

target_include_directories(sort_comparator_tests PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(sort_comparator_tests PRIVATE Catch2::Catch2WithMain)

include(${catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(sort_comparator_tests)
