#pragma once

#include <filesystem>

enum class Font {
    Blogger,
};

enum class Bitmap {
    Hero,
};

std::filesystem::path asset(Font font);
