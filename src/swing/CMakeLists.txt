add_executable(swing
    asset_map.cpp
    main.cpp
    paths.cpp
    resources.cpp
    screen.cpp
    screens/main_menu.cpp
    widgets/button.cpp
    widgets/label.cpp
)

target_include_directories (swing
    PRIVATE ${SDL_INCLUDE_DIR}
    PRIVATE ${SDL_GFX_INCLUDE_DIR}
    PRIVATE ${SDL_IMAGE_INCLUDE_DIR}
    PRIVATE ${SDL_TTF_INCLUDE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
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
