cmake_minimum_required(VERSION 3.25)
project(lru_cache)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wshadow -pedantic")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(
        lru_cache
        main.cpp
        include/lru_cache.h
        include/repository.h
        include/product_details.h
        src/repository.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(
        lru_cache_test
        test/doctest.h
        include/lru_cache.h
        include/repository.h
        include/product_details.h
        src/repository.cpp
        test/LRUTest.cpp
)
