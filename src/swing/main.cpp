#include "widget.hpp"
#include "paths.hpp"
#include "resources.hpp"
#include "widgets/label.hpp"
#include "widgets/button.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <memory>
#include <iostream>

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

    auto helloLabel = std::make_shared<Label>();
    helloLabel->position(960, 200);
    helloLabel->size(300, 100);
    helloLabel->font(Font::Blogger);
    helloLabel->text("Swing");
    helloLabel->color(150, 150, 0);

    auto newGameButton = std::make_shared<Button>();
    newGameButton->position(960, 400);
    newGameButton->size(400, 100);
    newGameButton->font(Font::Blogger);
    newGameButton->text("New Game");

    auto optionsButton = std::make_shared<Button>();
    optionsButton->position(960, 600);
    optionsButton->size(400, 100);
    optionsButton->font(Font::Blogger);
    optionsButton->text("Options");

    auto exitButton = std::make_shared<Button>();
    exitButton->position(960, 800);
    exitButton->size(400, 100);
    exitButton->font(Font::Blogger);
    exitButton->text("Exit");
    exitButton->action([] {
        SDL_Event quitEvent;
        quitEvent.type = SDL_QUIT;
        SDL_PushEvent(&quitEvent);
    });

    std::vector<std::shared_ptr<Widget>> widgets;
    widgets.push_back(std::move(helloLabel));
    widgets.push_back(std::move(newGameButton));
    widgets.push_back(std::move(optionsButton));
    widgets.push_back(std::move(exitButton));

    std::weak_ptr<Widget> widgetUnderCursor;
    std::weak_ptr<Widget> activeWidget;

    auto readEvents = [&widgets, &widgetUnderCursor, &activeWidget] {
        for (SDL_Event event; SDL_PollEvent(&event);) {
            switch (event.type) {
                case SDL_QUIT:
                    return false;

                case SDL_MOUSEMOTION:
                    widgetUnderCursor.reset();
                    for (const auto& widget : widgets) {
                        if (widget->contains(event.motion.x, event.motion.y)) {
                            widgetUnderCursor = widget;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (widgetUnderCursor.lock()) {
                        activeWidget = widgetUnderCursor;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (!activeWidget.expired() &&
                            activeWidget.lock() == widgetUnderCursor.lock()) {
                        activeWidget.lock()->perform();
                    }
                    activeWidget.reset();
                    break;
            }
        }
        return true;
    };

    while (true) {
        if (!readEvents()) {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 225, 225, 200, 255);
        SDL_RenderClear(renderer);

        auto active = activeWidget.lock();
        auto underCursor = widgetUnderCursor.lock();
        for (const auto& widget : widgets) {
            if (active) {
                if (widget == active) {
                    widget->draw(renderer, WidgetState::Active);
                } else {
                    widget->draw(renderer, WidgetState::Passive);
                }
            } else {
                if (widget == underCursor) {
                    widget->draw(renderer, WidgetState::Focused);
                } else {
                    widget->draw(renderer, WidgetState::Passive);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}
