#pragma once

#include <ecosnail/tail.hpp>

#include <SDL2/SDL.h>

template <class T> struct VectorDataXY {
    T x;
    T y;
};

using Position = ecosnail::tail::Vector<VectorDataXY, double>;

struct Animation {
    SDL_Texture* texture;
};
