cmake_minimum_required(VERSION 3.13)

project(SWGame
        VERSION 0.0.1
	    LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set (DEPENDENCY_DIR ${CMAKE_SOURCE_DIR}/lib)
set (SDL2DIR "${DEPENDENCY_DIR}/SDL2")
set (SDL2TTFDIR "${DEPENDENCY_DIR}/SDL2_ttf")
set (SDL2IMAGEDIR "${DEPENDENCY_DIR}/SDL2_image")
set (SDL2GFXDIR "${DEPENDENCY_DIR}/SDL2_gfx")
set (GALAXY_SDK_ROOT "${DEPENDENCY_DIR}/galaxy")
set (STEAMWORKS_SDK_ROOT "${DEPENDENCY_DIR}/steam")
set (STEAMWRAPPER_DIR "${DEPENDENCY_DIR}/GalaxySteamWrapper")

set (INSTALL_DIR ${CMAKE_SOURCE_DIR}/bin CACHE STRING "Instalation path")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${INSTALL_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${INSTALL_DIR})

find_package (STEAMWORKS REQUIRED)
if (NOT STEAMWORKS_FOUND)
	message (ERROR "Steamworks not found!")
endif()
include_directories (${STEAMWORKS_INCLUDE_DIR})

find_package (GALAXY REQUIRED)
if (NOT GALAXY_FOUND)
	message (ERROR "Galaxy not found!")
endif()
include_directories (${GALAXY_INCLUDE_DIR})

find_package (SDL2 REQUIRED)
if (NOT SDL2_FOUND)
	message (ERROR "SDL2 not found!")
endif()
include_directories (${SDL2_INCLUDE_DIR})

find_package (SDL2_ttf REQUIRED)
if (NOT SDL2TTF_FOUND)
	message (ERROR "SDL2_ttf not found!")
endif()
include_directories (${SDL2TTF_INCLUDE_DIR})

find_package (SDL2_image REQUIRED)
if (NOT SDL2IMAGE_FOUND)
	message (ERROR "SDL2_image not found!")
endif()
include_directories (${SDL2IMAGE_INCLUDE_DIR})

find_package (SDL2_gfx REQUIRED)
if (NOT SDL2GFX_FOUND)
	message (ERROR "SDL2_gfx not found!")
endif()
include_directories (${SDL2GFX_INCLUDE_DIR})

if (MSVC)
	add_definitions(/MP /std:c++latest)
else()
	add_definitions(-std=c++1z -g -Wall -Wno-unused-function)
endif()

add_subdirectory(src)