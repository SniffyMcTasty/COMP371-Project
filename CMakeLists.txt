cmake_minimum_required(VERSION 3.8)

project(shader_loader) 

# When testing large scenes the debug mode will be very slow
# so switch to release
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH
    /encs # For ENCS lab computers
    /opt/local # Macports
)

# These folders include some important header files including the header files for your own solution
#do not remove
include_directories(src/)
include_directories(external/)

#internal includes
aux_source_directory(external SOURCE)
aux_source_directory(src SOURCE)

add_executable(shader_viewer src/main.cpp ${SOURCE}) #The name of the cpp file and its path can vary

