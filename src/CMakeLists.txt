cmake_minimum_required(VERSION 2.8)

project(SimpleLog)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=gnu++0x")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})


include_directories(.)
aux_source_directory(. SRC)
add_library(simplelog STATIC ${SRC})

link_directories(${PROJECT_BINARY_DIR}/build)
link_libraries(simplelog)
link_libraries(pthread)
add_executable(testBasicLayout test/testBasicLayout.cpp)
add_executable(testOstreamAppender test/testOstreamAppender.cpp)
add_executable(testFileAppender test/testFileAppender.cpp)
add_executable(testDailyRollingFileAppender test/testDailyRollingFileAppender.cpp)
add_executable(testRollingFileAppender test/testRollingFileAppender.cpp)
add_executable(testTimeStamp test/testTimeStamp.cpp)
add_executable(testSimpleLog test/testSimpleLog.cpp)
#if test AsyncSimpleLog, do uncomment the ASYNC_LOG and make
add_executable(testAsyncSimpleLog test/testAsyncSimpleLog.cpp)
