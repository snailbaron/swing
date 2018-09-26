#pragma once

#include <SDL2/SDL.h>

enum class WidgetState {
    Passive,
    Focused,
    Active,
};

class Widget {
public:
    virtual ~Widget() {}

    virtual void draw(SDL_Renderer* renderer, WidgetState state) const = 0;
    virtual bool contains(int, int) const { return false; }
    virtual void perform() const {}
};
