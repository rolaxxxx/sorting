cmake_minimum_required(VERSION 2.8.12)

project(Daleliu_Pakavimas)
add_definitions(-DDEBUG_INFORMATION)
add_definitions(-DOPENCL_COMPILE_OPTIONS="-Werror" )
add_definitions(-DBOOST_COMPUTE_DEBUG_KERNEL_COMPILATION)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
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

set(SOURCE_FILES
    src/geometry.cpp
    src/geometry.h
    src/includes.h
    src/dalele.cpp
    src/dalele.h
    src/grid_count.cpp
    src/grid_count.h
    src/map_bounds.h
    src/map_bounds.cpp
    src/pakavimo_algoritmas.cpp
    src/pakavimo_algoritmas.h
    src/tasko_skaiciavimas.cpp
    src/tasko_skaiciavimas.h
    src/grid_neighbors.cpp
    src/coordinate_math.cpp
    src/coordinate_math.h
    src/grid_neighbors.h
)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

add_library(Biblioteka STATIC ${SOURCE_FILES})


add_executable(${PROJECT_NAME}     main.cpp)

target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES} -lpthread -lboost_log -lstdc++fs -lOpenCL Biblioteka)



add_executable(jj     main2.cpp )

target_link_libraries(jj  ${VTK_LIBRARIES} -lpthread -lboost_log -lstdc++fs -lOpenCL Biblioteka)
