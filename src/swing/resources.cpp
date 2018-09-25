#include "resources.hpp"
#include "paths.hpp"

#include <map>

namespace fs = std::filesystem;

namespace {

fs::path absPath(fs::path relPath)
{
    return exeDir() / "data" / relPath;
}

} // namespace

fs::path resourceFile(Font font)
{
    static const std::map<Font, fs::path> map {
        {Font::Blogger, "fonts/Blogger_Sans-Bold.otf"},
    };

    return absPath(map.at(font));
}
