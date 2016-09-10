
cmake_minimum_required(VERSION 3.3.0)

project(FOO CXX)
set(FOO_MAJOR_VERSION 1)
set(FOO_MINOR_VERSION 0)
set(FOO_PATCH_VERSION 0)
set(FOO_VERSION ${LAVA_MAJOR_VERSION}.${LAVA_MINOR_VERSION}.${LAVA_PATCH_VERSION})

get_filename_component(PROJECT_HOME "${CMAKE_SOURCE_DIR}" ABSOLUTE)
get_filename_component(SRC_DIR      "${PROJECT_HOME}/src" ABSOLUTE)

list(APPEND executable_sources "${SRC_DIR}/hello_world.cpp")
list(APPEND executable_sources "${SRC_DIR}/fibonacci.cpp")
list(APPEND executable_sources "${SRC_DIR}/pyramidal.cpp")

file(GLOB_RECURSE header_files "${SRC_DIR}/*.h")
file(GLOB_RECURSE source_files "${SRC_DIR}/*.cpp")

set(source_files_no_main ${source_files})
foreach(main_source ${executable_sources})
    LIST(REMOVE_ITEM source_files_no_main "${main_source}")
endforeach()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("-- Compiling for ${CMAKE_SYSTEM_NAME} with GCC...")
    set(CXX_FLAGS "-std=c++14 -fdiagnostics-color")
    set(CXX_WERR "-Wall -Wextra -Werror -Wmissing-format-attribute -Wmissing-noreturn -Wredundant-decls -Wsequence-point -Wdeprecated -Wunreachable-code -Wold-style-cast -Wfloat-equal -Wsuggest-attribute=noreturn -Wsign-conversion -Wdouble-promotion -Wshadow -Wno-effc++")
    set(CXX_WNOERR "-Wno-unused-parameter -Wno-conversion -Wno-padded")
endif()
    
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS} ${CXX_WERR} ${CXX_WNOERR}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(LOCAL_INCLUDE_DIRS "${SRC_DIR}")
set(SYSTEM_INCLUDE_DIRS "")
set(SYSTEM_LIBRARY_DIRS "")
set(SYSTEM_LIBRARIES "")

#include directories
include_directories(${LOCAL_INCLUDE_DIRS})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRS})

#link directories
link_directories(${SYSTEM_LIBRARY_DIRS})

# Compile and link static library (all code excluding mains)
if (source_files_no_main)
    set(CORE_LIB "Core")
    add_library(${CORE_LIB} STATIC ${source_files_no_main} ${template_files} ${header_files})
    target_link_libraries(${CORE_LIB} ${SYSTEM_LIBRARIES})
endif()

#Executables
foreach(main_source ${executable_sources})
    get_filename_component(exec_name ${main_source} NAME_WE)
    get_filename_component(exec_ext ${main_source} EXT)
    message("${exec_name}")
    message("${main_source}")

    add_executable(${exec_name} ${main_source})
    target_link_libraries(${exec_name} ${SYSTEM_LIBRARIES} ${CORE_LIB})
endforeach()
