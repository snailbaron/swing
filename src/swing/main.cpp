#include "widget.hpp"
#include "widgets.hpp"
#include "paths.hpp"
#include "resources.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <memory>

bool readEvents()
{
    for (SDL_Event event; SDL_PollEvent(&event);) {
        switch (event.type) {
            case SDL_QUIT:
                return false;
        }
    }

    return true;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
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

    auto helloLabel = std::make_unique<Label>();;
    helloLabel->position(0.5f, 0.2f);
    helloLabel->size(0.3f, 0.05f);
    helloLabel->font(Font::Blogger);
    helloLabel->text("New Game");
    helloLabel->color(150, 150, 0);

    std::vector<std::unique_ptr<Widget>> widgets;
    widgets.push_back(std::move(helloLabel));

    while (true) {
        if (!readEvents()) {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 225, 225, 200, 255);
        SDL_RenderClear(renderer);

        for (const auto& widget : widgets) {
            widget->draw(renderer, WidgetState::Passive);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}
