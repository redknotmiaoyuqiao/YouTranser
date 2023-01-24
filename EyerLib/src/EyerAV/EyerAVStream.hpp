#ifndef EYERLIB_EYERAVSTREAM_HPP
#define EYERLIB_EYERAVSTREAM_HPP

#include <stdio.h>
#include "EyerAVMediaType.hpp"
#include "EyerAVCodecID.hpp"
#include "EyerAVRational.hpp"
#include "EyerAVPixelFormat.hpp"
#include "EyerAVChannelLayout.hpp"
#include "EyerAVSampleFormat.hpp"

namespace Eyer
{
    class EyerAVStreamPrivate;

    class EyerAVStream {
    public:
        EyerAVStream();
        ~EyerAVStream();

        EyerAVStream(const EyerAVStream & stream);
        EyerAVStream(EyerAVStream && stream);

        EyerAVStream & operator = (const EyerAVStream & stream);

        const int GetStreamId() const;
        double GetDuration() const;

        const EyerAVMediaType GetType() const;
        const int GetWidth() const;
        const int GetHeight() const;
        EyerAVCodecID GetCodecID();

        EyerAVRational GetTimebase();

        EyerAVPixelFormat GetPixelFormat() const;

        EyerAVChannelLayout GetChannelLayout() const;
        int GetChannels() const;
        EyerAVSampleFormat GetSampleFormat() const;
        int GetSampleRate() const;
    public:
        EyerAVStreamPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVSTREAM_HPP
