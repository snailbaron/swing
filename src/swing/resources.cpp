#include "resources.hpp"

#include <SDL2/SDL_image.h>

#include <cassert>

namespace {

SDL_Texture* loadTexture(SDL_Renderer* renderer, Bitmap bitmap)
{
    SDL_Surface* surface = IMG_Load(resourceFile(bitmap).c_str());
    assert(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    assert(texture);

    SDL_FreeSurface(surface);

    return texture;
}

} // namespace

Resources::Resources(SDL_Renderer* renderer)
    : _renderer(renderer)
{
    static const std::vector<Bitmap> bitmaps {
        Bitmap::Hero,
    };

    for (auto bitmap : bitmaps) {
        _textures[bitmap] = loadTexture(_renderer, bitmap);
    }
}

Resources::~Resources()
{
    for (auto [bitmap, texture] : _textures) {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* Resources::texture(Bitmap bitmap) const
{
    return _textures.at(bitmap);
}
