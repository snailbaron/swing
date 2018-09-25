add_executable(swing
    main.cpp
    paths.cpp
    resources.cpp
    screen_coordinates.cpp
    widgets.cpp
)

target_include_directories (swing
    PRIVATE ${SDL_INCLUDE_DIR}
    PRIVATE ${SDL_GFX_INCLUDE_DIR}
    PRIVATE ${SDL_IMAGE_INCLUDE_DIR}
    PRIVATE ${SDL_TTF_INCLUDE_DIR}
)
target_link_libraries (swing
    ${SDL_LIBRARY}
    ${SDL_GFX_LIBRARY}
    ${SDL_IMAGE_LIBRARY}
    ${SDL_TTF_LIBRARY}
    stdc++fs
    tail
)

install (TARGETS swing DESTINATION ".")
