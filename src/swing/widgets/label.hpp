#pragma once

#include "widget.hpp"
#include "resources.hpp"
#include "screen_coordinates.hpp"

#include <SDL2/SDL.h>

class Label : public Widget {
public:
    Label();

    void draw(SDL_Renderer* renderer, WidgetState state) const override;

    Label& position(int x, int y);
    Label& size(int width, int height);
    Label& font(Font font);
    Label& text(std::string text);
    Label& color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

private:
    void checkCache(SDL_Renderer* renderer) const;

    mutable std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> _cachedTexture;
    mutable bool _cacheIsCold = true;
    mutable ScreenVector _screenSize;
    mutable ScreenVector _textureSize;

    ScreenVector _position;
    ScreenVector _size;
    Font _font;
    std::string _text;
    SDL_Color _color = {0, 0, 0, 255};
};

