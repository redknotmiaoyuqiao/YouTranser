#ifndef EYERLIB_EYERAVFILEFMT_HPP
#define EYERLIB_EYERAVFILEFMT_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVFileFmt
    {
    public:
        static EyerAVFileFmt UNKNOW;
        static EyerAVFileFmt MP4;
        static EyerAVFileFmt MOV;

    public:
        EyerAVFileFmt();
        EyerAVFileFmt(int _id, const EyerString & _suffix, const EyerString & _desc);

        ~EyerAVFileFmt();
        EyerAVFileFmt(const EyerAVFileFmt & avFileFmt);
        EyerAVFileFmt & operator = (const EyerAVFileFmt & avFileFmt);

        const bool operator == (const EyerAVFileFmt & avFileFmt) const;
        const bool operator != (const EyerAVFileFmt & avFileFmt) const;

        const EyerString & GetDesc() const;
        const EyerString & GetSuffix() const;

        const int GetId() const;

        static EyerAVFileFmt GetAVFileFmtById(int id);

    private:
        int id;
        EyerString suffix;
        EyerString desc;
    };
}

#endif //EYERLIB_EYERAVFILEFMT_HPP
