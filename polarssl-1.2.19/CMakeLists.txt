cmake_minimum_required(VERSION 2.8)

#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Release CACHE STRING "set build type to release")

#message(project_dir=${PROJECT_SOURCE_DIR})

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	message(FATAL_ERROR "Please into another dir to build!")
endif()

#string(TOUPPER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME)
if (CMAKE_SYSTEM_NAME MATCHES "Android")
	add_definitions("-DANDROID")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(WIN_OS true)
else()
	message(FATAL_ERROR "unknown CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
endif()

##############################################################################

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(src ${CMAKE_CURRENT_SOURCE_DIR}/library)
set(sources ${src})

foreach(iter ${sources})
	aux_source_directory(${iter} lib_src)
endforeach()

##############################################################################

#if (CMAKE_BUILD_TYPE STREQUAL "")
#	set(CMAKE_BUILD_TYPE "DEBUG")
#else()
#	string(TOUPPER CMAKE_BUILD_TYPE CMAKE_BUILD_TYPE)
#endif()

if (${UNIX_OS})
	add_definitions(
		"-W"
		"-O2"
		"-fPIC"
		"-Wall"
		"-Werror"
		"-Wshadow"
		"-Wpointer-arith"
		"-Waggregate-return"
		"-Wmissing-prototypes"
		"-D_REENTRANT"
		"-D_USE_FAST_MACRO"
		"-Wno-long-long"
		"-Wuninitialized"
		"-D_POSIX_PTHREAD_SEMANTICS"
		"-Wstrict-prototypes"
		"-D_FILE_OFFSET_BITS=64"
		"-Wdeclaration-after-statement"
	)

	if (CMAKE_COMPILER_IS_GNUCC)
		execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
			OUTPUT_VARIABLE GCC_VERSION)
		string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
		list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
		list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)

		if(CMAKE_VERSION GREATER "3.0")
			if ((GCC_MAJOR GREATER_EQUAL 4) AND (GCC_MINOR GREATER_EQUAL 8))
				message(STATUS "gcc version major=${GCC_MAJOR}")
				message(STATUS "gcc version minor=${GCC_MINOR}")
			endif()
		endif()
	endif()

	if (!CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
		add_definitions("-Wno-invalid-source-encoding")
	endif()

	if (CMAKE_SYSTEM_NAME MATCHES "Android")
		add_definitions("-Wno-inline-asm"
				"-D_SOCKLEN_T")
	endif()

	if (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
		add_definitions("-O2")
	else()
		add_definitions("-g")
	endif()
elseif (${WIN_OS})
	add_definitions(
		"-Yc"
		"-D_WINSOCK_DEPRECATED_NO_WARNINGS"
	)
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Android")
	set(CMAKE_SHARED_LINKER_FLAGS "-shared")
	set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/android/lib/${ANDROID_ABI})
	set(LIBRARY_OUTPUT_PATH ${lib_output_path})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${lib_output_path})

	add_library(polarssl_static STATIC ${lib_src})
	SET_TARGET_PROPERTIES(polarssl_static PROPERTIES OUTPUT_NAME "polarssl")
	link_directories(${lib_output_path})
else()
	set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
	set(LIBRARY_OUTPUT_PATH ${lib_output_path})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${lib_output_path})

	add_library(polarssl_static STATIC ${lib_src})
	SET_TARGET_PROPERTIES(polarssl_static PROPERTIES OUTPUT_NAME "polarssl")

	if (${WIN_OS})
		set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE ws2_32.lib IPHlpApi.lib")
	endif()
endif()

add_library(polarssl SHARED ${lib_src})

##############################################################################
