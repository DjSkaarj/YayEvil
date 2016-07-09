set (SOURCES 	actors.cpp
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

if (WINSIMPLE)
aux_source_directory(glew SOURCES)
endif()

# ignore glew.h
add_executable(yayevil ${SOURCES})
set_target_properties(yayevil PROPERTIES COTIRE_PREFIX_HEADER_IGNORE_PATH "${CMAKE_SOURCE_DIR}/src/glew/")

if (NOT NO_COTIRE)
cotire(yayevil)
endif()

if (NOT WINSIMPLE)
target_link_libraries(yayevil
	${SDL2_LIBRARY}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARY}
	${FREETYPE_LIBRARY}
	${SDL2IMAGE_LIBRARY}
)
endif()

if (WINSIMPLE)
target_link_libraries(yayevil "-lopengl32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image -lfreetype")
endif()
