cmake_minimum_required(VERSION 2.8)
project(trillek-server)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(ALL_INCLUDE_DIRS
	"${PROJECT_BINARY_DIR}"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/src/net/include"
	)

file(GLOB ALL_SRC
	"${CMAKE_SOURCE_DIR}/src/*"
	"${CMAKE_SOURCE_DIR}/src/net/src/*"
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
elseif(MSVC AND (MSVC10 OR MSVC11))
	message("Support Visual Studio!")
else("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")


# Set lib path for Windows
if(WIN32 AND NOT MINGW)
	if(MSVC)
		if(CMAKE_CL_64)
			set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/lib/x64)
			link_directories("${CMAKE_SOURCE_DIR}/lib/x64")
		else(CMAKE_CL_64)
			set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/lib/x86)
			link_directories("${CMAKE_SOURCE_DIR}/lib/x86")
		endif(CMAKE_CL_64)
	endif(MSVC)
endif(WIN32 AND NOT MINGW)

add_executable(trillek-server ${ALL_SRC} )
target_link_libraries(trillek-server )
#SET_TARGET_PROPERTIES(trillek-server PROPERTIES LINKER_LANGUAGE "C++")

