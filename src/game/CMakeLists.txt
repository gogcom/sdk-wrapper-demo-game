file (GLOB GAME_SRCS ${PROJECT_SOURCE_DIR}/src/game/*.cc ${PROJECT_SOURCE_DIR}/src/game/*h)
source_group ("game" FILES ${GAME_SRCS})

file (GLOB GAME_GUI_SRCS ${PROJECT_SOURCE_DIR}/src/game/gui/*.cc ${PROJECT_SOURCE_DIR}/src/game/gui/*h)
source_group ("gui" FILES ${GAME_GUI_SRCS})

file (GLOB GAME_SCENES_SRCS ${PROJECT_SOURCE_DIR}/src/game/scenes/*.cc ${PROJECT_SOURCE_DIR}/src/game/scenes/*h)
source_group ("scenes" FILES ${GAME_SCENES_SRCS})

file (GLOB GAME_STEAM_SRCS ${PROJECT_SOURCE_DIR}/src/game/steam/*.cc ${PROJECT_SOURCE_DIR}/src/game/steam/*h)
source_group ("steam" FILES ${GAME_STEAM_SRCS})

list (APPEND GAME_ALL_SRCS
	${GAME_SRCS}
    ${GAME_GUI_SRCS}
	${GAME_SCENES_SRCS}
	${GAME_STEAM_SRCS})

add_executable(SWGame ${GAME_ALL_SRCS})

list (APPEND EXTERNAL_LIBS engine ${STEAMWORKS_LIBRARY} ${SDL2_LIBRARY} ${SDL2IMAGE_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2GFX_LIBRARY} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY})

target_link_libraries(SWGame ${EXTERNAL_LIBS})

add_custom_command(TARGET SWGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
	"${CMAKE_SOURCE_DIR}/res"
	"${INSTALL_DIR}/${CMAKE_BUILD_TYPE}")

add_custom_command(TARGET SWGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${SDL2DIR}/lib/x64/SDL2.dll"
	"${INSTALL_DIR}/${CMAKE_BUILD_TYPE}")

add_custom_command(TARGET SWGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${SDL2TTFDIR}/lib/x64/SDL2_ttf.dll"
	"${INSTALL_DIR}/${CMAKE_BUILD_TYPE}")

add_custom_command(TARGET SWGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${SDL2IMAGEDIR}/lib/x64/SDL2_image.dll"
	"${INSTALL_DIR}/${CMAKE_BUILD_TYPE}")

add_custom_command(TARGET SWGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${SDL2GFXDIR}/lib/x64/SDL2_gfx.dll"
	"${INSTALL_DIR}/${CMAKE_BUILD_TYPE}")

add_custom_command(TARGET SWGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${CMAKE_SOURCE_DIR}/lib/GalaxySteamWrapper/Galaxy64.dll"
	"${INSTALL_DIR}/${CMAKE_BUILD_TYPE}")

add_custom_command(TARGET SWGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${CMAKE_SOURCE_DIR}/lib/GalaxySteamWrapper/GalaxySteamWrapper64.dll"
	"${INSTALL_DIR}/${CMAKE_BUILD_TYPE}/steam_api64.dll")