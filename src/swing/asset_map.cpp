#include "asset_map.hpp"
#include "paths.hpp"

#include <map>

namespace fs = std::filesystem;

namespace {

fs::path absPath(fs::path relPath)
{
    return exeDir() / "data" / relPath;
}

const std::map<Font, fs::path> fonts {
    {Font::Blogger, "fonts/Blogger_Sans-Bold.otf"},
};

const std::map<Bitmap, fs::path> bitmaps {
    {Bitmap::Hero, "bitmaps/hero.png"},
};

} // namespace

fs::path asset(Font font)
{
    return absPath(fonts.at(font));
}

std::filesystem::path asset(Bitmap bitmap)
{
    return absPath(bitmaps.at(bitmap));
}
