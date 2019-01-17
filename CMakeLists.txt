cmake_minimum_required(VERSION 2.8)
 
PROJECT(main)
add_definitions(-DDEBUG_INFORMATION)
add_definitions(-DOPENCL_COMPILE_OPTIONS="-Werror" )
add_definitions(-DBOOST_COMPUTE_DEBUG_KERNEL_COMPILATION)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS log )
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK=0)

include_directories(${Boost_INCLUDE_DIRS})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
find_package(OpenCL)
include_directories(${OpenCL_INCLUDE_DIR})   
include_directories(lib/embed-resource)
add_subdirectory(lib/embed-resource)
set(OPENCL_SOURCES
    src/Kernel.cl
)

set(SOURCE_FILES
    src/main.cxx
    src/main.h
)
embed_resources(MyResources ${OPENCL_SOURCES})

add_executable(main MACOSX_BUNDLE  ${SOURCE_FILES} ${MyResources} ${OPENCL_SOURCES})

SET(GCC_COMPILE_FLAGS "-w")
add_definitions(${GCC_COMPILE_FLAGS})
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${MY_GCC_COMPILE_FLAGS}" )


 
target_link_libraries(main ${VTK_LIBRARIES} -lpthread -lboost_log -lstdc++fs  -lOpenCL)
