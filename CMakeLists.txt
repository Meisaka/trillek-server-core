cmake_minimum_required(VERSION 2.8)
project(trillek-server)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(SERVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SERVER_INC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(RAPIDJSONROOT "" CACHE PATH "Path to rapidjson (non-standard locations)")

set(ALL_INCLUDE_DIRS
	"${PROJECT_BINARY_DIR}"
	"${SERVER_INC}"
	"${RAPIDJSONROOT}/include"
	)

file(GLOB NET_SRC
	"${SERVER_SRC}/net/src/*.c*"
	"${SERVER_SRC}/net/include/net/*.h*"
	)
source_group("net" FILES ${NET_SRC})

file(GLOB SIM_SRC
	"${SERVER_SRC}/simulations/*.c*"
	)
source_group("simulations" FILES ${SIM_SRC})

file(GLOB CONTEXT_SRC
	"${SERVER_SRC}/context/*.c*"
	"${SERVER_INC}/context/*.h*"
	)
source_group("context" FILES ${CONTEXT_SRC})

file(GLOB ENTITIES_SRC
	"${SERVER_SRC}/entities/*.c*"
	)
source_group("simulations" FILES ${ENTITIES_SRC})

file(GLOB MAIN_SRC
	"${SERVER_SRC}/*.c*"
	"${SERVER_INC}/*.h*"
	)

set(ALL_SRC
	${MAIN_SRC}
	${SIM_SRC}
	${CONTEXT_SRC}
	${ENTITIES_SRC}
	)
include_directories(${ALL_INCLUDE_DIRS})

# check for gcc version to set c++11 or c++0x
# thanks to http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
	if(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
		# c++11 std only appears in gcc 4.7 or higher. c++0x will work for lesser versions.
		message("gcc ${GCC_VERSION} does not support c++11, only c++0x. This may cause some problems in the future. We recommend upgrading to gcc-4.7 or greater.")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
		# compiler is gcc 4.7 or higher. Force c++11.
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
elseif(MSVC AND (MSVC_VERSION GREATER 1599))
	message("Support Visual Studio!")
else("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")


# Set lib path for Windows
if(MSVC)
	if(CMAKE_CL_64)
		set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/lib/x64)
		link_directories("${CMAKE_SOURCE_DIR}/lib/x64")
	else(CMAKE_CL_64)
		set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/lib/x86)
		link_directories("${CMAKE_SOURCE_DIR}/lib/x86")
	endif(CMAKE_CL_64)
endif(MSVC)

add_subdirectory(net)
include_directories(net/include)

add_executable(trillek-server ${ALL_SRC})
target_link_libraries(trillek-server netport)
#SET_TARGET_PROPERTIES(trillek-server PROPERTIES LINKER_LANGUAGE "C++")

