cmake_minimum_required (VERSION 3.7)

project (PKP)

# include directories
include_directories ("/Users/vascella/.local/include")
link_directories ("/Users/vascella/.local/lib")


#set ( CMAKE_C_FLAGS "-std=gnu++11")
# add_definitions("-std=gnu++14")
set (CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES model.cpp runner.cpp)

add_library(pkp SHARED ${SOURCE_FILES})

# test
add_executable(test.x test.cpp)
target_link_libraries(test.x pkp gtest)

# main
add_executable(main.x main.cpp)
target_link_libraries(main.x pkp)


#add_executable(test.x gtest.cpp)
#target_link_libraries(test.x test gtest)
