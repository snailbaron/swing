#include "widget.hpp"
#include "paths.hpp"
#include "resources.hpp"
#include "widgets/label.hpp"
#include "widgets/button.hpp"
#include "resources.hpp"
#include "components.hpp"

#include <ecosnail/thing.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <memory>
#include <iostream>

using ecosnail::thing::EntityManager;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow(
        "Swing",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Resources resources(renderer);
    EntityManager entityManager;

    auto hero = entityManager.createEntity();

    auto& heroPosition = entityManager.add<Position>(hero);
    heroPosition.x = 0.0;
    heroPosition.y = 0.0;

    auto& heroAnimation = entityManager.add<Animation>(hero);
    heroAnimation.texture = resources.texture(Bitmap::Hero);

    while (true) {
        bool done = false;
        for (SDL_Event event; SDL_PollEvent(&event);) {
            if (event.type == SDL_QUIT) {
                done = true;
                break;
            }
        }
        if (done) {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 225, 225, 200, 255);
        SDL_RenderClear(renderer);

        for (auto entity : entityManager.entities<Animation>()) {
            const auto& position = entityManager.component<Position>(entity);
            const auto& animation = entityManager.component<Animation>(entity);

            SDL_RenderCopy(renderer, animation.texture, nullptr, 
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
