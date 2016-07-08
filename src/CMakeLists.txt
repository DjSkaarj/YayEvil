add_executable(yayevil
	actors.cpp
	font.cpp
	fontloader.cpp
	geometry.cpp
	log.cpp
	main.cpp
	map.cpp
	math.cpp
	mouse.cpp
	renderer.cpp
	strings.cpp
	tiles.cpp
)

target_link_libraries(yayevil
	${SDL2_LIBRARY}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARY}
	${FREETYPE_LIBRARY}
	${SDL2IMAGE_LIBRARY}
)

