cmake_minimum_required(VERSION 2.6)

project(irrlichtfinal)

list(APPEND CMAKE_CXX_FLAGS "-m64 -std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(UseLATEX)

# if(WIN32)
# 	if(MSVC)
#       if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# 		    install_files(media/ bin/Debug/media )
# 	    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
# 	        install_files(bin/Release/media media)
# 		endif()
# 	endif()
# elseif(UNIX)
# 	install_targets(bin media)
# elseif(APPLE)
#     mac users
# endif()

add_subdirectory(pdf)
add_subdirectory(src)

