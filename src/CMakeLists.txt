macro (find_header_and_lib NAME HEADER LIB)
    find_path (${NAME}_INCLUDE_DIR ${HEADER})
    if (NOT ${NAME}_INCLUDE_DIR)
        message (FATAL_ERROR "Failed to find header: ${HEADER}")
    endif ()

    find_library (${NAME}_LIBRARY ${LIB})
    if (NOT ${NAME}_LIBRARY)
        message (FATAL_ERROR "Failed to find library: ${LIB}")
    endif ()
endmacro ()

find_header_and_lib (SDL SDL2/SDL.h SDL2)
find_header_and_lib (SDL_GFX SDL2/SDL2_gfxPrimitives.h SDL2_gfx)
find_header_and_lib (SDL_IMAGE SDL2/SDL_image.h SDL2_image)
find_header_and_lib (SDL_TTF SDL2/SDL_ttf.h SDL2_ttf)

add_subdirectory(swing)
