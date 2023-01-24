#ifndef EYERLIB_EYERAVTRANSCODE_HPP
#define EYERLIB_EYERAVTRANSCODE_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVTranscodeParams.hpp"
#include "EyerAVStream.hpp"
#include "EyerAVEncoder.hpp"
#include "EyerAVWriter.hpp"
#include "EyerAVReader.hpp"
#include "EyerAVDecoder.hpp"
#include "EyerAVDecoderBox.hpp"
#include "EyerAVResample.hpp"

namespace Eyer
{
    class EyerAVTranscode
    {
    public:
        EyerAVTranscode(const EyerString & _srcPath, const EyerString & _targetPath, const EyerAVTranscodeParams & _params);
        ~EyerAVTranscode();

        int Transcode();

    private:
        double GetDuration(int index);

        EyerAVWriter writer;

        EyerAVEncoder videoEncoder;
        int encoderVideoStreamIndex = -1;
        EyerAVEncoder audioEncoder;
        EyerAVResample resample;
        int encoderAudioStreamIndex = -1;
        int InitEncoder(EyerAVWriter & writer);


        EyerAVReader videoReader;
        EyerAVDecoder videoDeocder;
        int decoderVideoStreamIndex = -1;
        EyerAVReader audioReader;
        EyerAVDecoder audioDecoder;
        int decoderAudioStreamIndex = -1;
        int InitDeocder();
        int UninitDeocder();

        EyerAVDecoderBox decoderBox;
        long frameCount = 0;
        double videoDuration = 0.0;

        int TranscodeAudio(double limitTime);
        int TranscodeVideo(double limitTime, long & frameOffset);
        int EncodeAudio(EyerAVFrame & frame);

        EyerString srcPath;
        EyerString targetPath;
        EyerAVTranscodeParams params;

        int audioOffset = 0;
    };
}

#endif //EYERLIB_EYERAVTRANSCODE_HPP
