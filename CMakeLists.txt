cmake_minimum_required(VERSION 3.1)

project(xml_order)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(STATICLIBS)
  set(LIB_TYPE STATIC)
else()
  set(LIB_TYPE SHARED)
endif()

# include_directories(~/boost_1_60_0/)

# include_directories(src)

# file(GLOB_RECURSE xml_order_SRC ./*.cpp) add_library(xml2cpp ${LIB_TYPE}
# ${xml_order_SRC})

file(GLOB_RECURSE test_SRC ./src/*.cpp)
add_executable(test ${test_SRC})
target_link_libraries(test LINK_PUBLIC curl xerces-c pthread)
