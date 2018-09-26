#include "widgets/label.hpp"

#include <SDL2/SDL_ttf.h>

#include <cassert>

Label::Label()
    : _cachedTexture(nullptr, SDL_DestroyTexture)
{ }

Label& Label::position(int x, int y)
{
    _position.x = x;
    _position.y = y;
    return *this;
}

Label& Label::size(int width, int height)
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

    SDL_Rect dstRect {
        _position.x - _textureSize.x / 2,
        _position.y - _textureSize.y / 2,
        _textureSize.x,
        _textureSize.y
    };

    SDL_RenderCopy(renderer, _cachedTexture.get(), nullptr, &dstRect);
}

void Label::checkCache(SDL_Renderer* renderer) const
{
    if (_cacheIsCold) {
        auto resFile = resourceFile(_font);
        TTF_Font* font = TTF_OpenFont(resFile.c_str(), _size.y);
        assert(font);

        int w;
        TTF_SizeUTF8(font, _text.c_str(), &w, nullptr);
        if (w > _size.x) {
            int newSize = _size.y * _size.x / w;
            font = TTF_OpenFont(resFile.c_str(), newSize);
            assert(font);
        }

        SDL_Surface* surface =
            TTF_RenderUTF8_Blended(font, _text.c_str(), _color);
        //SDL_Surface* surface =
        //    TTF_RenderUTF8_Shaded(font, _text.c_str(), _color, SDL_Color{200, 200, 200, 255});
        assert(surface);
        _textureSize = {surface->w, surface->h};

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        assert(texture);

        _cachedTexture.reset(texture);
        _cacheIsCold = false;

        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
    }
}

