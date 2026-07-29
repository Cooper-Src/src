#include "package_manifest.hpp"

namespace src
{
    bool PackageManifest::valid() const
    {
        return
        !name.empty() &&
        !source.type.empty() &&
        !version.empty() &&
        !source.url.empty();
    }
}