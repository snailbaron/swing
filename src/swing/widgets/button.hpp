#pragma once

#include "resources.hpp"
#include "widget.hpp"
#include "widgets/label.hpp"
#include "screen_coordinates.hpp"

#include <SDL2/SDL.h>

#include <functional>

class Button : public Widget {
public:
    void draw(SDL_Renderer* renderer, WidgetState state) const override;
    bool contains(int x, int y) const override;
    void perform() const override;

    Button& position(int x, int y);
    Button& size(int width, int height);
    Button& font(Font font);
    Button& text(std::string text);
    Button& action(std::function<void()> action);

private:
    ScreenVector _position;
    ScreenVector _size;
    int _borderSize;
    int _textOffset;
    Label _label;
    std::function<void()> _action = []{};
};
