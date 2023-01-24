#ifndef EYERLIB_EYERAVSAMPLERATE_HPP
#define EYERLIB_EYERAVSAMPLERATE_HPP

namespace Eyer
{
    class EyerAVSampleRate
    {
    public:
        static EyerAVSampleRate SR_44100;
        static EyerAVSampleRate SR_48000;
        static EyerAVSampleRate SR_96000;

        EyerAVSampleRate(int _id, int _sampleRate);
        EyerAVSampleRate();
        EyerAVSampleRate(const EyerAVSampleRate & sampleRate);
        ~EyerAVSampleRate();

        const EyerAVSampleRate & operator = (const EyerAVSampleRate & sampleRate);
        const bool operator == (const EyerAVSampleRate & sampleRate);
        const bool operator != (const EyerAVSampleRate & sampleRate);

        const int GetId() const;
        const int GetSampleRate() const;

    private:
        int id;
        int sampleRate;
    };
}

#endif //EYERLIB_EYERAVSAMPLERATE_HPP
