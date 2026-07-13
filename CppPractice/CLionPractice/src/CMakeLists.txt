find_package(Boost CONFIG REQUIRED)

add_executable(CLionTest main.cpp)
target_include_directories(CLionTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CLionTest PRIVATE Boost::headers)
