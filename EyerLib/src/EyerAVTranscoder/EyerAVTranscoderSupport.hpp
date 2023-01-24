#ifndef EYERLIB_EYERAVTRANSCODERSUPPORT_HPP
#define EYERLIB_EYERAVTRANSCODERSUPPORT_HPP

#include <vector>

#include "EyerAV/EyerAVHeader.hpp"

namespace Eyer
{
    class EyerAVTranscoderSupport
    {
    public:
        std::vector<EyerAVFileFmt> QuerySupportFmt();
        std::vector<EyerAVCodecID> QuerySupportVideoCodec(const EyerAVFileFmt & fileFmt);
        std::vector<EyerAVCodecID> QuerySupportAudioCodec(const EyerAVFileFmt & fileFmt);

        std::vector<EyerAVPixelFormat> QuerySupportPixelFormat(const EyerAVCodecID & codecId);

        std::vector<EyerAVChannelLayout> QuerySupportChannelLayout(const EyerAVCodecID & codecId);
        std::vector<int> QuerySupportSampleRate(const EyerAVCodecID & codecId);

        EyerAVSampleFormat GetHighestSampleFmt(const EyerAVCodecID & codecId);

        bool IsPixelFmtSupports(const EyerAVCodecID & codecId, const EyerAVPixelFormat & pixfmt);
        bool IsAudioChannelSupports(const EyerAVCodecID & codecId, const EyerAVChannelLayout & audioChannel);
        bool IsSampleRateSupports(const EyerAVCodecID & codecId, int sampleRate);
    };
}

#endif //EYERLIB_EYERAVTRANSCODERSUPPORT_HPP
