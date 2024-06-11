#ifndef EYERLIB_EYERAVSNAPSHOTLINE_HPP
#define EYERLIB_EYERAVSNAPSHOTLINE_HPP

#include "EyerAVReader.hpp"
#include "EyerAVFrame.hpp"
#include "EyerAVDecoder.hpp"

namespace Eyer
{
    class EyerAVSnapshotLine
    {
    public:
        EyerAVSnapshotLine(const EyerString & _path, const EyerAVStream & _videoStream, int _videoStreamIndex, double _pts, EyerAVReaderCustomIO * _customIO);
        ~EyerAVSnapshotLine();

        int GetFrame(std::shared_ptr<EyerAVFrame> & frame, double pts);

        double GetStartTime();

    private:
        int SearchFrameInCache(std::shared_ptr<EyerAVFrame> & frame, double pts);
        int DecodeFrame();
        int ClearCache(int maxDropFrames);

    private:
        EyerString mPath = "";
        EyerAVReaderCustomIO * mCustomIO = nullptr;

        EyerAVStream mVideoStream;
        int mVideoStreamIndex = -1;

        std::shared_ptr<EyerAVReader> reader = nullptr;
        std::shared_ptr<EyerAVDecoder> decoder = nullptr;

        std::vector<std::shared_ptr<EyerAVFrame>> frameCache;

        std::queue<std::shared_ptr<EyerAVFrame>> tempFrameCache;

        double startSeekTime = 0.0;
    };
}

#endif //EYERLIB_EYERAVSNAPSHOTLINE_HPP
