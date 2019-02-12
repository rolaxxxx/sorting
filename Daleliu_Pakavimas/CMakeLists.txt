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
    geometry.cpp
    geometry.h

    includes.h
    dalele.cpp
    dalele.h
    grid_count.cpp
    grid_count.h
    map_bounds.h
    map_bounds.cpp
    pakavimo_algoritmas.cpp
    pakavimo_algoritmas.h
    tasko_skaiciavimas.cpp
    tasko_skaiciavimas.h
    grid_neighbors.cpp
    coordinate_math.cpp
    coordinate_math.h
    grid_neighbors.h
)
find_package(Qt5Core)

add_executable(${PROJECT_NAME}     main.cpp ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Core ${VTK_LIBRARIES} -lpthread -lboost_log -lstdc++fs -lOpenCL)



add_executable(jj     main2.cpp ${SOURCE_FILES})

target_link_libraries(jj Qt5::Core ${VTK_LIBRARIES} -lpthread -lboost_log -lstdc++fs -lOpenCL)
