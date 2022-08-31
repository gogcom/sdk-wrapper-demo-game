set (STEAMWORKS_PATHS	${STEAMWORKS_SDK_ROOT}
					$ENV{STEAMWORKS_SDK_ROOT}
					${STEAMWORKS_SDK_ROOT}/public/steam
					${STEAMWORKS_SDK_ROOT}/public/steam/lib
					~/Library/Frameworks
					/Library/Frameworks
					/usr/local
					/user
					/sw
					/opt/local
					/opt/csw
					/opt
					${CMAKE_SOURCE_DIR}/steam)

find_path(STEAMWORKS_INCLUDE_DIR steam_api.h PATH_SUFFIXES steam/public/steam PATHS ${STEAMWORKS_PATHS})
find_library(STEAMWORKS_LIBRARY NAMES steam_api64 PATH_SUFFIXES steam/redistributable_bin/win64 PATHS ${STEAMWORKS_PATHS})

if (STEAMWORKS_INCLUDE_DIR AND STEAMWORKS_LIBRARY)
	set(STEAMWORKS_FOUND TRUE)
else()
	set(STEAMWORKS_FOUND FALSE)
endif()
