# ? While FetchContent only requires CMake 3.11, selecting C++20 through
# ? CMAKE_CXX_STANDARD requires 3.12 and the convenience function
# ? `FetchContent_MakeAvailable` was introduced in CMake 3.14
cmake_minimum_required(VERSION 3.14.0)
project(WHEELED_WARRIOR VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ? Where we can find cmake modules
set(CMAKE_MODS "${CMAKE_SOURCE_DIR}/cmake_modules")

# ? Choose to open terminal when debugging and get rid of it on release
include("${CMAKE_MODS}/ApplicationType.cmake")

# ?
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ? Fetch SDL2 libraries
include("${CMAKE_MODS}/ThirdPartyDependencies.cmake")

# ? Actual usage will be kept for every target in the separate file
# ? 'targets' - all targets here
set(MAIN WheeledWarrior)

# * Icon
# ! Implement for Linux also
set(APP_ICON_WIN "${CMAKE_SOURCE_DIR}/icon.rc")

# if(WIN32)
# set(ICON_RESOURCE "assets/resources/saw_wheel.ico")
# set_property(SOURCE "source/${MAIN}.cpp" PROPERTY VS_DESKTOP_EXTENSIONS ${ICON_RESOURCE})
# endif()

# ? Set up all paths for the custom libraries
include("${CMAKE_MODS}/CustomLibrariesPaths.cmake")

# ? All libraries and main executable would be created with output properties
# ? so tell how all of them output
include("${CMAKE_MODS}/OutputProperties.cmake")

# ? MSVC shows warnings that can be hide
include("${CMAKE_MODS}/HideMVSCWarnings.cmake")

# ? Build all libraries needed
include("${CMAKE_MODS}/AddLibraries.cmake")

# ? Link game application to the source cpp - building the game that way
include("${CMAKE_MODS}/BuildGame.cmake")

# ? Include and Link OneTBB source code and libraries
include("${CMAKE_MODS}/UseOneTBB.cmake")

# ? Set specific compiler flags
include("${CMAKE_MODS}/CompilerFlags.cmake")

# ? Game executable would need assets folder at the same directory
include("${CMAKE_MODS}/ExtractAssets.cmake")

# ? Game executable would need shared libraries at the same directory
include("${CMAKE_MODS}/ExtractThirdPartyLibraries.cmake")
