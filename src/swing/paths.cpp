#include "paths.hpp"

#ifdef linux
#   include <unistd.h>
#endif

namespace fs = std::filesystem;

fs::path exeDir()
{
    std::string pathString(1024, '\0');

    ssize_t written;
    while((written = readlink(
            "/proc/self/exe",
            pathString.data(),
            pathString.size())) == pathString.size()) {
        pathString.resize(pathString.size() * 2);
    }
    pathString.resize(written);

    return fs::path(std::move(pathString)).parent_path();
}
