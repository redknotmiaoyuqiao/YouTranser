#ifndef EYERLIB_EYERMEDIAINFOPARSE_HPP
#define EYERLIB_EYERMEDIAINFOPARSE_HPP

#include "EyerMediaInfo.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerMediaInfoParse
    {
    public:
        EyerMediaInfoParse();
        ~EyerMediaInfoParse();

        int Parse(const EyerString & path);

        EyerMediaInfo GetInfo();

    private:
        EyerMediaInfo mediaInfo;
    };
};

#endif //EYERLIB_EYERMEDIAINFOPARSE_HPP
