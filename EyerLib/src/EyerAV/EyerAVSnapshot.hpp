#ifndef EYERLIB_EYERAVSNAPSHOT_HPP
#define EYERLIB_EYERAVSNAPSHOT_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVReaderCustomIO.hpp"
#include "EyerAVFrame.hpp"
#include "EyerAVStream.hpp"
#include "EyerAVSnapshotLine.hpp"

namespace Eyer
{
    class EyerAVSnapshot
    {
    public:
        EyerAVSnapshot(const EyerString & _path, EyerAVReaderCustomIO * _customIO = nullptr);
        ~EyerAVSnapshot();

        int Init();

        std::shared_ptr<EyerAVFrame> GetFrame(double pts);

    private:
        std::shared_ptr<EyerAVSnapshotLine> FindSnapshotLine(double pts);

    private:
        EyerString mPath = "";
        EyerAVReaderCustomIO * mCustomIO = nullptr;

        EyerAVStream mVideoStream;
        int mVideoStreamIndex = -1;

        std::vector<std::shared_ptr<EyerAVSnapshotLine>> mDecoderLineCache;
    };
}



#endif //EYERLIB_EYERAVSNAPSHOT_HPP
