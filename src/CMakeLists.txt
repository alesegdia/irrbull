# Name the sources
file( GLOB_RECURSE SRCs */*.cpp )
file( GLOB_RECURSE INCs */*.h )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Irrlicht REQUIRED)
find_package(Bullet REQUIRED)
find_package(aruco REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(irrbull ${SRCs} ${INCs})

include_directories(.)

if(BOOST_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(irrbull ${Boost_LIBRARIES})
endif()

if(IRRLICHT_FOUND)
	include_directories(${IRRLICHT_INCLUDE_DIRS})
	target_link_libraries(irrbull ${IRRLICHT_LIBRARIES})
endif()

if(BULLET_FOUND)
	include_directories(${BULLET_INCLUDE_DIRS})
	target_link_libraries(irrbull ${BULLET_LIBRARIES})
endif()


# Set output
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)
