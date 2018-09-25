#pragma once

#include <filesystem>

enum class Font {
    Blogger
};

std::filesystem::path resourceFile(Font font);
