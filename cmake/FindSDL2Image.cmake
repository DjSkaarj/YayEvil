# GNU sdl2 image 
if(SDL2IMAGE_INCLUDE_DIR AND SDL2IMAGE_LIBRARY)
  set(SDL2IMAGE_FOUND TRUE)
else(SDL2IMAGE_INCLUDE_DIR AND SDL2IMAGE_LIBRARY)

  #mac with port install
  find_path(
    SDL2IMAGE_INCLUDE_DIR
    SDL2/SDL_image.h
    PATHS
    /opt/local/include/
    NO_DEFAULT_PATH)

  find_library(
    SDL2IMAGE_LIBRARY 
    sdl2_image
    /opt/local/lib
    NO_DEFAULT_PATH)


  #linux 
  find_path(
    SDL2IMAGE_INCLUDE_DIR
    SDL2/SDL_image.h)
  find_library(
    SDL2IMAGE_LIBRARY
    SDL2_image)
	
  #windows
  find_path(
    SDL2IMAGE_INCLUDE_DIR
    SDL2/SDL_image.h
    PATHS
    "C:/Program Files/SDL"
    NO_DEFAULT_PATH)

  find_library(
    SDL2IMAGE_LIBRARY 
    sdl2_image
    "C:/Program Files/SDL/lib/x86"
    NO_DEFAULT_PATH)



  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(sdl2image DEFAULT_MSG SDL2IMAGE_INCLUDE_DIR SDL2IMAGE_LIBRARY )
  mark_as_advanced(SDL2IMAGE_INCLUDE_DIR SDL2IMAGE_LIBRARY)
endif(SDL2IMAGE_INCLUDE_DIR AND SDL2IMAGE_LIBRARY)
