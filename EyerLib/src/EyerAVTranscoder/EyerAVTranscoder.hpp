#ifndef EYERLIB_EYERAVTRANSCODER_HPP
#define EYERLIB_EYERAVTRANSCODER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVTranscoderParams.hpp"
#include "EyerAVTranscodeStream.hpp"
#include "EyerAVTranscoderStatus.hpp"
#include "EyerAVTranscoderError.hpp"
#include "EyerAV/EyerAVReaderCustomIO.hpp"

#define SAMPLE_RATE_KEEP_SAME -2

namespace Eyer
{
    class EyerAVTranscoderListener
    {
    public:
        virtual int OnProgress(float progress) = 0;
        virtual int OnFail(EyerAVTranscoderError & error) = 0;
        virtual int OnSuccess() = 0;
    };

    class EyerAVTranscoderInterrupt
    {
    public:
        virtual bool interrupt() = 0;
    };

    class EyerAVTranscoder
    {
    public:
        EyerAVTranscoder(const EyerString & _inputPath);
        ~EyerAVTranscoder();

        int SetOutputPath(const EyerString & outputPath);
        int SetParams(const EyerAVTranscoderParams & params);
        int SetListener(EyerAVTranscoderListener * _listener);

        int Transcode_(EyerAVTranscoderInterrupt * interrupt);
        int Transcode(EyerAVTranscoderInterrupt * interrupt, EyerAVReaderCustomIO * customIO = nullptr);

        EyerAVTranscoderStatus GetStatus();
        int SetStatus(const EyerAVTranscoderStatus & _status);

        EyerString GetErrorDesc();
        int SetErrorDesc(const EyerString & _errorDesc);
    private:
        EyerAVTranscoderStatus status = EyerAVTranscoderStatus::PREPARE;
        EyerString errorDesc = "";

        EyerString inputPath;
        EyerString outputPath;

        EyerAVTranscoderParams params;

        int InitEncoder(EyerAVEncoder * encoder, const EyerAVStream & stream);
        int EncodeFrame(Eyer::EyerAVWriter * write, EyerAVTranscodeStream * ts, EyerAVFrame & frame);
        int ClearFrame(Eyer::EyerAVWriter * write, EyerAVTranscodeStream * ts);

        double duration = 0.0;
        double lastUpdateTime = 0.0;

        EyerAVTranscoderListener * listener = nullptr;

        long long totleTime = 0;
        long long ioReadTime = 0;
        long long ioWriteTime = 0;
    };
}

#endif //EYERLIB_EYERAVTRANSCODER_HPP
