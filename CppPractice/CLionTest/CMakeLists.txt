cmake_minimum_required(VERSION 3.6)
project(CLionTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(SOURCE_FILES src/main.cpp src/stdafx.h src/TypeTraits.h)
add_executable(CLionTest ${SOURCE_FILES})


set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
set (Boost_USE_MULTITHREAD ON)  # enable multithreading

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

find_package (Boost COMPONENTS REQUIRED system)

target_link_libraries(CLionTest LINK_PUBLIC ${Boost_LIBRARIES})