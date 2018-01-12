cmake_minimum_required (VERSION 3.7)

project (PKP)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# include directories
include_directories ("/Users/vascella/.local/include")
include_directories ("./src")
link_directories ("/Users/vascella/.local/lib")

#set ( CMAKE_C_FLAGS "-std=gnu++11")
# add_definitions("-std=gnu++14")
set (CMAKE_CXX_STANDARD 14)

# https://stackoverflow.com/questions/36078456/cmake-add-include-paths-to-clang
# generates the file compile_commands.json.
# With this file the include directives are working correctly.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# cmake -DCMAKE_BUILD_TYPE=Debug ..
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# set(SOURCE_FILES model.cpp reactor.cpp SFOR.cpp C2SM.cpp ModelFactory.cpp)
# set(SOURCE_FILES src/*.cpp)
file(GLOB project_sources src/*.cpp)

add_library(pkp SHARED ${project_sources})

# test
add_executable(test.x test/test.cpp)
target_link_libraries(test.x pkp gtest)

# test reactorT
add_executable(test_reactorT.x test/test_reactorT.cpp)
target_link_libraries(test_reactorT.x pkp gtest)

# main
add_executable(main.x test/main.cpp)
target_link_libraries(main.x pkp yaml-cpp)

# main
add_executable(test_factory.x test/test_factory.cpp)
target_link_libraries(test_factory.x pkp)

#add_executable(test.x gtest.cpp)
#target_link_libraries(test.x test gtest)
