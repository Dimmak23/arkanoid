# ? While FetchContent only requires CMake 3.11, selecting C++20 through
# ? CMAKE_CXX_STANDARD requires 3.12 and the convenience function
# ? `FetchContent_MakeAvailable` was introduced in CMake 3.14
cmake_minimum_required(VERSION 3.14.0)
project(ARKANOID VERSION 2.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ? Where we can find cmake modules
set(CMAKE_MODS "${CMAKE_SOURCE_DIR}/cmake_modules")

# ?
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ? Set the TBB library path for Multithreading
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(TBB_ROOT_LIB "${CMAKE_SOURCE_DIR}/third_party/oneTBB/mingw64/mingw64/bin" CACHE PATH "Path to TBB") # Change this path according to your oneTBB location
	set(TBB_ROOT_INC "${CMAKE_SOURCE_DIR}/third_party/oneTBB/mingw64/mingw64/include" CACHE PATH "Path to TBB") # Change this path according to your oneTBB location
endif()

# ? Set the path to the third-party libraries
set(OpusFile_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/opusfile/bin")
set(FLAC_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/flac/bin/libFLAC.dll") # ! But why?
set(libxmp_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/libxmp/bin")
set(FluidSynth_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/fluidsynth/bin")
set(wavpack_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/wavpack/bin")
set(FREETYPE_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/freetype/bin/freetype.dll") # ! But why?

# ? Set the path to the third-party source codes
set(OpusFile_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/third_party/opusfile/include")
set(FLAC_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/third_party/flac/include")
set(libxmp_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/third_party/libxmp/include")
set(FluidSynth_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/third_party/fluidsynth/include")
set(wavpack_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/third_party/wavpack/include")
set(FREETYPE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/third_party/freetype/include")

# ? Explicitly and globaly include third-party source codes
include_directories(
	PRIVATE "${CMAKE_SOURCE_DIR}/third_party/ogg/include"
	PRIVATE "${CMAKE_SOURCE_DIR}/third_party/opus/include"
)

# I would like to keep every target binary in it's own dir,
# also 'Debug' and 'Release' dir's inside them as well
# 'executables' - all executables root

# ?
set(EXECUTABLE_ROOT "${CMAKE_SOURCE_DIR}/executables")

# ?
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		set(OUTPUT_DIR "${EXECUTABLE_ROOT}/Debug")
	else()
		set(OUTPUT_DIR "${EXECUTABLE_ROOT}/Release")
	endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(OUTPUT_DIR_D ${EXECUTABLE_ROOT})
endif()

# ? Define a function to set common target properties
function(set_output_properties TARGET) # BUILD_TYPE == DEBUG || RELEASE
	set_target_properties(
		${TARGET}
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}" # Binary
		LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}" # Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}" # Static libraries
	)
endfunction()

# ? Fetch SFML libraries

# ?
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # To allow cmake print intermidiate comments

# ?
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

# ! What is the main source file?
set(MAIN Arkanoid)

# ? Where is spurce libraries is kept
set(LIBRARIES "${CMAKE_SOURCE_DIR}/libs")

# ? Where is header only libraries is kept
set(HEADERS "${CMAKE_SOURCE_DIR}/headers")

# ? Which type of libraries is it gonna be?
set(LIB_TYPE "SHARED")

# ? Create main executable
add_library(
	application
	${LIB_TYPE}
	${LIBRARIES}/application/GameApplication.cpp
	${HEADERS}/game_page_dynamics.cpp
	${HEADERS}/game_page_statics.cpp
	${HEADERS}/game_page_process.cpp
)

# ? Include needed folders
target_include_directories(
	application
	PUBLIC ${LIBRARIES}/dynamics
	PUBLIC ${LIBRARIES}/outline
	PUBLIC ${LIBRARIES}/process
	PUBLIC ${LIBRARIES}/statics
	PUBLIC ${HEADERS}
)

# ? Link needed libraries
target_link_libraries(
	application
	PUBLIC sfml-graphics
	PUBLIC sfml-audio
	PUBLIC sfml-system
	PUBLIC sfml-window
)

# ? Create main executable
add_executable(
	${MAIN}
	source/${MAIN}.cpp
)

# ? Include needed folders
target_include_directories(
	${MAIN}
	PUBLIC ${LIBRARIES}/application
)

# ? Link needed libraries
target_link_libraries(
	${MAIN}
	PRIVATE application
)

# ?
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(TBB_LIB "-llibtbb12")

	target_include_directories(
		${MAIN}
		PRIVATE ${TBB_ROOT_INC}
	)

	target_link_directories(
		${MAIN}
		PRIVATE "${TBB_ROOT_LIB}"
	)

	target_link_libraries(
		${MAIN}
		PRIVATE ${TBB_LIB}
	)
endif()

# ?
set_output_properties(${MAIN})

# ? We using SFML as shared libraries so they should be in the same directory with Game executable
if(WIN32) # ! Why Linux don't need it?
	set(EXTENSION_NAME "dll")
	set(PREFIX "")

	# Define function to copy DLL's on Windows
	function(copy_custom_dll MODULE)
		set(PREFIX "lib")

		if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			set(POSTFIX_DLL_NAME "") # set to 'd' when Debug
		else()
			set(POSTFIX_DLL_NAME "")
		endif()

		add_custom_command(
			TARGET ${MAIN} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE_DIR:${MODULE}>/${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
			"$<TARGET_FILE_DIR:${MAIN}>/${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
		)
	endfunction()

	# Define function to copy DLL's on Windows
	function(copy_dll MODULE)
		if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			set(POSTFIX_DLL_NAME "-d-2") # set to 'd' when Debug
		else()
			set(POSTFIX_DLL_NAME "-2")
		endif()

		add_custom_command(
			TARGET ${MAIN} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE_DIR:${MODULE}>/${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
			"$<TARGET_FILE_DIR:${MAIN}>/${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
		)
	endfunction()

	# Define function to copy DLL's on Windows
	function(copy_std_dll MODULE)
		set(POSTFIX_DLL_NAME "12")
		set(PREFIX "lib")

		add_custom_command(
			TARGET ${MAIN} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${TBB_ROOT_LIB}/${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
			"$<TARGET_FILE_DIR:${MAIN}>/${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
		)
	endfunction()

	copy_custom_dll(application)
	copy_dll(sfml-audio)
	copy_dll(sfml-graphics)
	copy_dll(sfml-system)
	copy_dll(sfml-window)
	copy_std_dll(tbb)
endif()
