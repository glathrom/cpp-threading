cmake_minimum_required(VERSION 3.16)
project(threads)
set(CMAKE_CXX_STANDARD 20)

######################################################
# setting paths for libraries and executable outputs
######################################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

######################################################
# setting path to include files 
######################################################

include_directories( 
    ${CMAKE_SOURCE_DIR}/include 
) 

######################################################
# finding a library to link against
######################################################

#if( ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm" )
#    find_library(pthreadlib pthread PATHS /usr/arm-linux-gnueabihf/lib NO_DEFAULT_PATH)
#    find_library(boostlogsetuplib boost_log_setup PATHS /usr/arm-linux-gnueabihf/lib NO_DEFAULT_PATH)
#    find_library(boostloglib boost_log PATHS /usr/arm-linux-gnueabihf/lib NO_DEFAULT_PATH)
#else()
#    find_library(pthreadlib pthread)
#    find_library(boostlogsetuplib boost_log_setup)
#    find_library(boostloglib boost_log)
#endif()

find_library(pthreadlib pthread)
find_library(boostlogsetuplib boost_log_setup)
find_library(boostloglib boost_log)

######################################################
# set the source and add a target
######################################################

set(CMAKE_CXX_FLAGS -DBOOST_LOG_DYN_LINK)

set(SOURCES ${CMAKE_SOURCE_DIR}/src/program2.cpp)
add_executable(program2 ${SOURCES})
target_link_libraries(program2 ${pthreadlib} ${boostlogsetuplib} ${boostloglib})


set(SOURCES ${CMAKE_SOURCE_DIR}/src/program1.cpp)
add_executable(program1 ${SOURCES})
target_link_libraries(program1 ${pthreadlib} )
