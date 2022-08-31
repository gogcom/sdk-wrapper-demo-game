set (GALAXY_PATHS	${GALAXY_SDK_ROOT}
					$ENV{GALAXY_SDK_ROOT}
					${GALAXY_SDK_ROOT}/Include
					${GALAXY_SDK_ROOT}/Libraries
					~/Library/Frameworks
					/Library/Frameworks
					/usr/local
					/user
					/sw
					/opt/local
					/opt/csw
					/opt
					/galaxy
					${CMAKE_SOURCE_DIR}/galaxy)

find_path(GALAXY_INCLUDE_DIR galaxy/GalaxyApi.h PATHS ${GALAXY_PATHS})
find_library(GALAXY_LIBRARY NAMES Galaxy64 PATHS ${GALAXY_PATHS})

if (GALAXY_INCLUDE_DIR AND GALAXY_LIBRARY)
	set(GALAXY_FOUND TRUE)
else()
	set(GALAXY_FOUND FALSE)
endif()
