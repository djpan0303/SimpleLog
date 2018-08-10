cmake_minimum_required(VERSION 3.5)

project(SimpleLog)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})


include_directories(.)
aux_source_directory(. SRC)
add_library(simplelog STATIC ${SRC})

link_directories(${PROJECT_BINARY_DIR}/build)
link_libraries(simplelog)
add_executable(testBasicLayout test/testBasicLayout.cpp)
add_executable(testOstreamAppender test/testOstreamAppender.cpp)
add_executable(testFileAppender test/testFileAppender.cpp)
add_executable(testDailyRollingFileAppender test/testDailyRollingFileAppender.cpp)
add_executable(testRollingFileAppender test/testRollingFileAppender.cpp)
add_executable(testTimeStamp test/testTimeStamp.cpp)
