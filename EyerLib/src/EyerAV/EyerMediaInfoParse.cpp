#include "EyerMediaInfoParse.hpp"

#include "EyerAVReader.hpp"

namespace Eyer
{
    EyerMediaInfoParse::EyerMediaInfoParse()
    {

    }

    EyerMediaInfoParse::~EyerMediaInfoParse()
    {

    }

    int EyerMediaInfoParse::Parse(const EyerString & path)
    {
        EyerAVReader reader(path);
        int ret = reader.Open();
        if(ret){
            return -1;
        }

        int audioStreamIndex = reader.GetAudioStreamIndex();
        if(audioStreamIndex >= 0){
            EyerAVStream stream = reader.GetStream(audioStreamIndex);
            mediaInfo.AddStream(stream);
        }

        int videoStreamIndex = reader.GetVideoStreamIndex();
        if(videoStreamIndex >= 0){
            EyerAVStream stream = reader.GetStream(videoStreamIndex);
            mediaInfo.AddStream(stream);
        }

        return 0;
    }

    EyerMediaInfo EyerMediaInfoParse::GetInfo()
    {
        return mediaInfo;
    }
}