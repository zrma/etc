cmake_minimum_required(VERSION 3.20)
project(ModernCppFunctional LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost CONFIG REQUIRED)

file(GLOB_RECURSE MODERN_CPP_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/ModernCppFunctional/*.cpp"
)

add_executable(ModernCppFunctional ${MODERN_CPP_SOURCES})
target_include_directories(ModernCppFunctional PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ModernCppFunctional"
)
target_link_libraries(ModernCppFunctional PRIVATE Boost::headers)
