#include "widgets/button.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

#include <utility>
#include <cassert>
#include <map>

bool Button::contains(int x, int y) const
{
    return x >= _position.x - _size.x / 2 &&
        x < _position.x + _size.x / 2 &&
        y >= _position.y - _size.y / 2 &&
        y < _position.y + _size.y / 2;
}

Button& Button::position(int x, int y)
{
    _position = {x, y};
    _label.position(x, y);
    return *this;
}

Button& Button::size(int width, int height)
{
    _size = {width, height};
    _borderSize = std::min(width, height) / 15;
    _textOffset = std::min(width, height) / 3;
    _label.size(
        width - 2 * _borderSize - _textOffset,
        height - 2 * _borderSize - _textOffset);
    return *this;
}

Button& Button::font(Font font)
{
    _label.font(font);
    return *this;
}

Button& Button::text(std::string text)
{
    _label.text(text);
    return *this;
}

Button& Button::action(std::function<void()> action)
{
    _action = std::move(action);
    return *this;
}

void Button::draw(SDL_Renderer* renderer, WidgetState state) const
{
    static const std::map<WidgetState, SDL_Color> outerColors {
        {WidgetState::Passive, {255, 0, 0, 255}},
        {WidgetState::Focused, {150, 0, 0, 255}},
        {WidgetState::Active, {80, 0, 0, 255}},
    };

    const auto& outerColor = outerColors.at(state);

    roundedBoxRGBA(
        renderer,
        _position.x - _size.x / 2,
        _position.y - _size.y / 2,
        _position.x + _size.x / 2,
        _position.y + _size.y / 2,
        _borderSize,
        outerColor.r, outerColor.g, outerColor.b, outerColor.a);
    roundedBoxRGBA(
        renderer,
        _position.x - _size.x / 2 + _borderSize,
        _position.y - _size.y / 2 + _borderSize,
        _position.x + _size.x / 2 - _borderSize,
        _position.y + _size.y / 2 - _borderSize,
        _borderSize,
        0, 255, 0, 255);
    _label.draw(renderer, state);
}

void Button::perform() const
{
    _action();
}
