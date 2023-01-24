#include "EyerMediaInfo.hpp"

namespace Eyer
{
    EyerMediaInfo::EyerMediaInfo()
    {

    }

    EyerMediaInfo::~EyerMediaInfo()
    {

    }

    EyerMediaInfo::EyerMediaInfo(const EyerMediaInfo & mediaInfo)
    {
        *this = mediaInfo;
    }

    EyerMediaInfo & EyerMediaInfo::operator = (const EyerMediaInfo & mediaInfo)
    {
        for(int i=0;i<mediaInfo.streamList.size();i++){
            streamList.push_back(mediaInfo.streamList[i]);
        }
        return *this;
    }

    int EyerMediaInfo::AddStream(const EyerAVStream & stream)
    {
        streamList.push_back(stream);
        return 0;
    }

    int EyerMediaInfo::GetStreamSize()
    {
        return streamList.size();
    }

    EyerAVStream EyerMediaInfo::GetStream(int index)
    {
        return streamList[index];
    }
}