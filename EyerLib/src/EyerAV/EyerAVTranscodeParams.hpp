#ifndef EYERLIB_EYERAVTRANSCODEPARAMS_HPP
#define EYERLIB_EYERAVTRANSCODEPARAMS_HPP

namespace Eyer
{
    class EyerAVTranscodeParams
    {
    public:
        EyerAVTranscodeParams();
        EyerAVTranscodeParams(const EyerAVTranscodeParams & params);

        EyerAVTranscodeParams & operator = (const EyerAVTranscodeParams & params);

        int targetWidth = 0;
        int targetHeight = 0;
        float fps = 30.0;

        bool careVideo = true;
        bool careAudio = true;
    };
}

#endif //EYERLIB_EYERAVTRANSCODEPARAMS_HPP
