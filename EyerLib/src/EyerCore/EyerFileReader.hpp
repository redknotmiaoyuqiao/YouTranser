#ifndef EYERLIB_EYERFILEREADER_HPP
#define EYERLIB_EYERFILEREADER_HPP

#include "EyerString.hpp"

namespace Eyer
{
    class EyerFileReader
    {
    public:
        EyerFileReader(const EyerString & path);
        ~EyerFileReader();

        EyerString ReadText();

    private:
        EyerString path;
    };
}

#endif //EYERLIB_EYERFILEREADER_HPP
