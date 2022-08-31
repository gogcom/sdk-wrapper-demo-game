find_path(SDL2_GFX_INCLUDE_DIR SDL2_gfxPrimitives.h
  HINTS
    ${SDL2GFXDIR}
    ${SDL2DIR}
    #ENV SDLTTFDIR
    #ENV SDLDIR
  PATH_SUFFIXES include/SDL2_gfxPrimitives include
  PATHS
  ../SDL2_gfx/prefix
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/SDL
  /usr/include/SDL
  /usr/local/include/SDL12
  /usr/local/include/SDL11 # FreeBSD ports
  /usr/include/SDL12
  /usr/include/SDL11
  /usr/local/include
  /usr/include
  /sw/include/SDL # Fink
  /sw/include
  /opt/local/include/SDL # DarwinPorts
  /opt/local/include
  /opt/csw/include/SDL # Blastwave
  /opt/csw/include 
  /opt/include/SDL
  /opt/include
)

find_library(SDL2_GFX_LIBRARY
  NAMES SDL2_gfx
  HINTS
    ${SDL2GFXDIR}
	${SDL2DIR}
  PATH_SUFFIXES lib lib/x64
  PATHS
  ../SDL2_gfx/prefix
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

if(SDL2_GFX_INCLUDE_DIR AND EXISTS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h")
  file(STRINGS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h" SDL2_GFX_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_GFX_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h" SDL2_GFX_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_GFX_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h" SDL2_GFX_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_GFX_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_GFX_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_GFX_VERSION_MAJOR "${SDL2_GFX_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_GFX_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_GFX_VERSION_MINOR "${SDL2_GFX_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_GFX_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_GFX_VERSION_PATCH "${SDL2_GFX_VERSION_PATCH_LINE}")
  set(SDL2_GFX_VERSION_STRING ${SDL2_GFX_VERSION_MAJOR}.${SDL2_GFX_VERSION_MINOR}.${SDL2_GFX_VERSION_PATCH})
  unset(SDL2_GFX_VERSION_MAJOR_LINE)
  unset(SDL2_GFX_VERSION_MINOR_LINE)
  unset(SDL2_GFX_VERSION_PATCH_LINE)
  unset(SDL2_GFX_VERSION_MAJOR)
  unset(SDL2_GFX_VERSION_MINOR)
  unset(SDL2_GFX_VERSION_PATCH)
endif()

set(SDL2_GFX_LIBRARIES ${SDL2_GFX_LIBRARY})
set(SDL2_GFX_INCLUDE_DIRS ${SDL2_GFX_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_gfx
                                  REQUIRED_VARS SDL2_GFX_LIBRARIES SDL2_GFX_INCLUDE_DIRS
                                  VERSION_VAR SDL2_GFX_VERSION_STRING)

# for backward compatiblity
set(SDL2GFX_LIBRARY ${SDL2_GFX_LIBRARIES})
set(SDL2GFX_INCLUDE_DIR ${SDL2_GFX_INCLUDE_DIRS})
set(SDL2GFX_FOUND ${SDL2_GFX_FOUND})

mark_as_advanced(SDL2_GFX_LIBRARY SDL2_GFX_INCLUDE_DIR)
