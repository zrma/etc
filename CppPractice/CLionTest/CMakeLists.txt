cmake_minimum_required(VERSION 3.6)
project(CLionTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(CLionTest ${SOURCE_FILES})


#------------------------------------------------------------------------------
# Required CPM Setup - no need to modify - See: https://github.com/iauns/cpm
#------------------------------------------------------------------------------
set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
find_package(Git)
if (NOT GIT_FOUND)
    message(FATAL_ERROR "CPM requires Git.")
endif ()
if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
    message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
    execute_process(
            COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
            RESULT_VARIABLE error_code
            OUTPUT_QUIET ERROR_QUIET)
    if (error_code)
        message(FATAL_ERROR "CPM failed to get the hash for HEAD")
    endif ()
endif ()
include(${CPM_DIR}/CPM.cmake)

#------------------------------------------------------------------------------
# CPM Modules
#------------------------------------------------------------------------------

# TODO: Include any modules here...

CPM_AddModule("boost"
        GIT_REPOSITORY "https://github.com/toeb/cpm-boost")

CPM_AddModule("json"
        GIT_REPOSITORY "https://github.com/nlohmann/json")

CPM_Finish()