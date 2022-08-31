file (GLOB ENGINE_SRCS ${PROJECT_SOURCE_DIR}/src/engine/*.cc ${PROJECT_SOURCE_DIR}/src/engine/*h)
source_group ("engine" FILES ${ENGINE_SRCS})

list (APPEND ENGINE_ALL_SRCS
	${ENGINE_SRCS})

add_library (engine STATIC ${ENGINE_ALL_SRCS})
target_link_libraries (engine ${EXTERNAL_LIBS})