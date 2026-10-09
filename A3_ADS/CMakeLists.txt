cmake_minimum_required(VERSION 3.16)
project(A3_ADS)

set(CMAKE_CXX_STANDARD 20)

add_executable(A3_ADS main.cpp
        SortedBag.cpp
        SortedBagIterator.cpp
        ShortTest.cpp
        ExtendedTest.cpp
)

enable_testing()
add_test(NAME sorted_bag_tests COMMAND A3_ADS)
