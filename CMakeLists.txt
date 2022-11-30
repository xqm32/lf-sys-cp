cmake_minimum_required(VERSION 3.16)
project(PROJECT_NAME)

include_directories(include)
aux_source_directory(src SRC)

if(${BUFFSIZE})
    add_definitions(-DBUFFSIZE=${BUFFSIZE})
endif()

add_compile_options(-std=c17)
add_executable(lfcp src/lfcp.c)
add_executable(syscp src/syscp.c)