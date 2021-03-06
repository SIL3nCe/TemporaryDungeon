cmake_minimum_required(VERSION 3.1)

project(SteelTraining)

include(cmake/package.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_SHARED_LINKER_FLAGS "${ShSDK_SHARED_LINKER_FLAGS}")

# Find Shine Engine/Editor libraries
set(USE_MODULE)
if(SHINE_INTERNAL)
	set(USE_MODULE NO_MODULE)
endif(SHINE_INTERNAL)

find_package(ShSDK REQUIRED StubUserSystem ShEntryPoint ${USE_MODULE})
find_package(ShSDKEditor REQUIRED ${USE_MODULE})

# Include some cmake helpers
include(cmake/Master.cmake)
include(cmake/TargetBuildSAAS.cmake)

ConfigureShineSAAS()

option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" OFF)
option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" OFF)
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" ON)

add_subdirectory(Box2D/Box2D Box2D)

add_subdirectory(src)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Game")
