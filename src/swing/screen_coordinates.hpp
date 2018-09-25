#pragma once

#include <SDL2/SDL.h>

struct PixelVector {
    int x;
    int y;
};

bool operator==(const PixelVector& lhs, const PixelVector& rhs);
bool operator!=(const PixelVector& lhs, const PixelVector& rhs);

struct ScreenCoordinate {
    ScreenCoordinate() : pixels(0), part(0) {}
    ScreenCoordinate(int pixels) : pixels(pixels), part(0) {}
    ScreenCoordinate(float part) : pixels(0), part(part) {}

    int pixels;
    float part;
};

struct ScreenVector {
    PixelVector pixels(SDL_Renderer* renderer) const;

    ScreenCoordinate x;
    ScreenCoordinate y;
};
