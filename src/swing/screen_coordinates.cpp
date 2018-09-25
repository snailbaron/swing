#include "screen_coordinates.hpp"

#include <cmath>
#include <tuple>

bool operator==(const PixelVector& lhs, const PixelVector& rhs)
{
    return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}

bool operator!=(const PixelVector& lhs, const PixelVector& rhs)
{
    return std::tie(lhs.x, lhs.y) != std::tie(rhs.x, rhs.y);
}

PixelVector ScreenVector::pixels(SDL_Renderer* renderer) const
{
    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

    return {
        static_cast<int>(lround(x.pixels + x.part * screenWidth)),
        static_cast<int>(lround(y.pixels + y.part * screenHeight))
    };
}
