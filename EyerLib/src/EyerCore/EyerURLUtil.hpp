#ifndef EYERLIB_EYERURLUTIL_HPP
#define EYERLIB_EYERURLUTIL_HPP

#include "EyerString.hpp"

namespace Eyer{
    class EyerURLUtil {
    public:
        EyerURLUtil(const EyerString & baseUrl);
        ~EyerURLUtil();

        EyerString GetAbsolutePath(const EyerString & relativePath);

    private:
        EyerString baseUrl;
    };
}

#endif //EYERLIB_EYERURLUTIL_HPP
