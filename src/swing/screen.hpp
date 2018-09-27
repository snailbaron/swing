#pragma once

#include "widget.hpp"

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

class Screen {
public:
    void processEvent(const SDL_Event& event);
    void draw(SDL_Renderer* renderer) const;

private:
    std::vector<std::shared_ptr<Widget>> _widgets;
    std::weak_ptr<Widget> _activeWidget;
    std::weak_ptr<Widget> _widgetUnderCursor;
};
