cmake_minimum_required (VERSION 3.7)

project (PKP)

# include directories
include_directories ("/Users/vascella/.local/include")
link_directories ("/Users/vascella/.local/lib")


#set ( CMAKE_C_FLAGS "-std=gnu++11")
# add_definitions("-std=gnu++14")
set (CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES model.cpp reactor.cpp SFOR.cpp C2SM.cpp ModelFactory.cpp)

add_library(pkp SHARED ${SOURCE_FILES})

# test
add_executable(test.x test.cpp)
target_link_libraries(test.x pkp gtest)

# test reactorT
add_executable(test_reactorT.x test_reactorT.cpp)
target_link_libraries(test_reactorT.x pkp gtest)

# main
add_executable(main.x main.cpp)
target_link_libraries(main.x pkp yaml-cpp)

# main
add_executable(test_factory.x test_factory.cpp)
target_link_libraries(test_factory.x pkp)

#add_executable(test.x gtest.cpp)
#target_link_libraries(test.x test gtest)
