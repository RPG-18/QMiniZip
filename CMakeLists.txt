project(qminizip)
cmake_minimum_required(VERSION 2.8)

option(TEST "enable tests" OFF)

find_package(ZLIB REQUIRED)

find_package(Qt5Core REQUIRED)
set(CMAKE_AUTOMOC ON)

include_directories(${ZLIB_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS})
add_definitions(${Qt5Core_DEFINITIONS})

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")    
endif()

add_subdirectory(src)

if(TEST)
    enable_testing()
    add_subdirectory(3rdparty/gtest)
    include_directories(src
                        3rdparty/gtest/include)    
    add_subdirectory(test)
endif()