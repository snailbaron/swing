#include "widgets.hpp"

#include <utility>
#include <cassert>

Label::Label()
    : _cachedTexture(nullptr, SDL_DestroyTexture)
{ }

Label& Label::position(float x, float y)
{
    _position.x = x;
    _position.y = y;
    return *this;
}

Label& Label::size(float width, float height)
{
    _size.x = width;
    _size.y = height;
    _cacheIsCold = true;
    return *this;
}

Label& Label::font(Font font)
{
    _font = font;
    _cacheIsCold = true;
    return *this;
}

Label& Label::text(std::string text)
{
    _text = std::move(text);
    _cacheIsCold = true;
    return *this;
}

Label& Label::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    _color = {r, g, b, a};
    _cacheIsCold = true;
    return *this;
}

void Label::draw(SDL_Renderer* renderer, WidgetState) const
{
    checkCache(renderer);

    auto pixelPosition = _position.pixels(renderer);

    SDL_Rect dstRect {
        pixelPosition.x - _textureSize.x / 2,
        pixelPosition.y - _textureSize.y / 2,
        _textureSize.x,
        _textureSize.y
    };

    SDL_RenderCopy(renderer, _cachedTexture.get(), nullptr, &dstRect);
}

void Label::checkCache(SDL_Renderer* renderer) const
{
    PixelVector screenSize;
    SDL_GetRendererOutputSize(renderer, &screenSize.x, &screenSize.y);

    if (screenSize != _screenSize) {
        _screenSize = screenSize;
        _cacheIsCold = true;
    }

    if (_cacheIsCold) {
        auto pixelSize = _size.pixels(renderer);

        auto resFile = resourceFile(_font);
        TTF_Font* font = TTF_OpenFont(resFile.c_str(), pixelSize.y);

        assert(font);
        SDL_Surface* surface =
            TTF_RenderUTF8_Blended(font, _text.c_str(), _color);
        _textureSize = {surface->w, surface->h};
        assert(surface);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        assert(texture);
        _cachedTexture.reset(texture);
        _cacheIsCold = false;

        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
    }
}
