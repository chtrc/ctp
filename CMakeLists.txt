
# cmake_minimum_required (VERSION 2.8)

# project(ctp)

# add_executable(main main.cpp)

# include_directories(include)

# # SET(PROJECT_SOURCE_DIR /home/yy/ctp)
# add_library(libmd SHARED IMPORTED)
# set_target_properties(libmd PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/libthostmduserapi_se.so)

# add_library( libtd SHARED IMPORTED )
# set_target_properties(libtd PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/libthosttraderapi_se.so)
# # link_directories("/home/yy/ctp/lib")
# target_link_libraries(main libmd libtd)

cmake_minimum_required(VERSION 3.15)
 
PROJECT(main)
 
# set(CMAKE_CXX_FLAGS "-fPIC -O3")
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
# 默认输出debug版
#SET(CMAKE_BUILD_TYPE "Release")
# SET(CMAKE_BUILD_TYPE "debug")
# set(CMAKE_CXX_STANDARD 11)
 
set(CTP_INCLUDE ${CMAKE_SOURCE_DIR}/include)
include_directories(${CTP_INCLUDE})
 
set(CTP_LIB ${CMAKE_SOURCE_DIR}/lib)
link_directories(${CTP_LIB})
 
set(SOURCES main.cpp CTPMarketDataSource.cpp)
add_executable(${PROJECT_NAME} main.cpp CTPMarketDataSource.cpp)
target_link_libraries(${PROJECT_NAME} thostmduserapi_se pthread)