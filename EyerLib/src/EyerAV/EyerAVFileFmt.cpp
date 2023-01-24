#include "EyerAVFileFmt.hpp"

namespace Eyer
{
    EyerAVFileFmt EyerAVFileFmt::UNKNOW (-1,    "unknow",   "unknow");
    EyerAVFileFmt EyerAVFileFmt::MP4    (0,     "mp4",      "MP4");
    EyerAVFileFmt EyerAVFileFmt::MOV    (1,     "mov",      "MOV");

    EyerAVFileFmt::EyerAVFileFmt()
    {

    }

    EyerAVFileFmt::EyerAVFileFmt(int _id, const EyerString & _suffix, const EyerString & _desc)
        : id(_id)
        , suffix(_suffix)
        , desc(_desc)
    {

    }

    EyerAVFileFmt::~EyerAVFileFmt()
    {

    }

    EyerAVFileFmt::EyerAVFileFmt(const EyerAVFileFmt & avFileFmt)
    {
        *this = avFileFmt;
    }

    EyerAVFileFmt & EyerAVFileFmt::operator = (const EyerAVFileFmt & avFileFmt)
    {
        id      = avFileFmt.id;
        suffix  = avFileFmt.suffix;
        desc    = avFileFmt.desc;
        return *this;
    }

    const bool EyerAVFileFmt::operator == (const EyerAVFileFmt & avFileFmt) const
    {
        return id == avFileFmt.id;
    }

    const bool EyerAVFileFmt::operator != (const EyerAVFileFmt & avFileFmt) const
    {
        return id != avFileFmt.id;
    }

    const EyerString & EyerAVFileFmt::GetDesc() const
    {
        return desc;
    }

    const EyerString & EyerAVFileFmt::GetSuffix() const
    {
        return suffix;
    }

    const int EyerAVFileFmt::GetId() const
    {
        return id;
    }

    EyerAVFileFmt EyerAVFileFmt::GetAVFileFmtById(int id)
    {
        if(id == MP4.GetId()){
            return MP4;
        }
        else if(id == MOV.GetId()){
            return MOV;
        }
        return UNKNOW;
    }
}