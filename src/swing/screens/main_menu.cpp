#include "main_menu.hpp"
#include "widgets/label.hpp"
#include "widgets/button.hpp"

namespace screen {

std::vector<std::shared_ptr<Widget>> mainMenu()
{
    std::vector<std::shared_ptr<Widget>> widgets;

    auto title = std::make_shared<Label>();
    title->position(960, 200);
    title->size(300, 100);
    title->font(Font::Blogger);
    title->text("Swing");
    title->color(150, 150, 0);
    widgets.push_back(std::move(title));

    auto newGameButton = std::make_shared<Button>();
    newGameButton->position(960, 400);
    newGameButton->size(400, 100);
    newGameButton->font(Font::Blogger);
    newGameButton->text("New Game");
    widgets.push_back(std::move(newGameButton));

    auto optionsButton = std::make_shared<Button>();
    optionsButton->position(960, 600);
    optionsButton->size(400, 100);
    optionsButton->font(Font::Blogger);
    optionsButton->text("Options");
    widgets.push_back(std::move(optionsButton));

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
    widgets.push_back(std::move(exitButton));

    return widgets;
}

} // namespace screen
