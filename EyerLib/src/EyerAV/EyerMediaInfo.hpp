#ifndef EYERLIB_EYERMEDIAINFO_HPP
#define EYERLIB_EYERMEDIAINFO_HPP

#include <vector>

#include "EyerAVStream.hpp"

namespace Eyer
{
    class EyerMediaInfo
    {
    public:
        EyerMediaInfo();
        ~EyerMediaInfo();

        EyerMediaInfo(const EyerMediaInfo & mediaInfo);
        EyerMediaInfo & operator = (const EyerMediaInfo & mediaInfo);

        int AddStream(const EyerAVStream & stream);

        int GetStreamSize();
        EyerAVStream GetStream(int index);

    private:
        std::vector<EyerAVStream> streamList;
    };
}

#endif //EYERLIB_EYERMEDIAINFO_HPP
