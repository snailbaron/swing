#pragma once

#include "asset_map.hpp"

#include <SDL2/SDL.h>

#include <map>

class Resources {
public:
    explicit Resources(SDL_Renderer* renderer);
    ~Resources();

    SDL_Texture* texture(Bitmap bitmap) const;

private:
    SDL_Renderer* _renderer;
    std::map<Bitmap, SDL_Texture*> _textures;
};
