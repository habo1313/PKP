cmake_minimum_required (VERSION 2.6)
include_directories ("/Users/vascella/.local/include")
link_directories ("/Users/vascella/.local/lib")
project (PKP)

#set ( CMAKE_C_FLAGS "-std=gnu++11")
add_definitions("-std=gnu++14")

add_library(pkp SHARED model.cpp runner.cpp)

# test
add_executable(test.x test.cpp)
target_link_libraries(test.x pkp gtest)

# main
add_executable(main.x main.cpp)
target_link_libraries(main.x pkp)


#add_executable(test.x gtest.cpp)
#target_link_libraries(test.x test gtest)
