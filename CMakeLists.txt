cmake_minimum_required(VERSION 3.12)

project(boost_log CXX)
set(CMAKE_CXX_STANDARD 11)

if (WIN32)
	set(Boost_USE_STATIC_LIBS ON)
	set(Boost_USE_MULTITHREADED ON)
else (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
	set(Boost_USE_STATIC_LIBS OFF)
	set(Boost_USE_MULTITHREADED ON)
	add_definitions(-DBOOST_ALL_DYN_LINK)
endif (WIN32)

# Boost::log required Boost version >= 1.65.0 
find_package(Boost 1.65.0 REQUIRED COMPONENTS log log_setup)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(SRC_FILES
    src/main.cpp)

add_executable(boost_log ${SRC_FILES})
target_link_libraries(boost_log ${Boost_LIBRARIES} )

add_executable(boost_log2 src/main2.cpp)
target_link_libraries(boost_log2 ${Boost_LIBRARIES} )


