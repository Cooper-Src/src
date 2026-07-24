#include "package_manifest.hpp"

namespace src
{
    bool PackageManifest::valid() const
    {
        return
            !name.empty() &&
            !version.empty() &&
            !sourceType.empty() &&
            !sourceUrl.empty();
    }
}