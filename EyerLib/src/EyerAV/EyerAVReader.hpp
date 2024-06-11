#ifndef EYERLIB_EYERAVREADER_HPP
#define EYERLIB_EYERAVREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVPacket.hpp"
#include "EyerAVStream.hpp"
#include "EyerAVReaderCustomIO.hpp"

namespace Eyer
{
    class EyerAVReaderPrivate;

    class EyerAVReader {
    public:
        EyerAVReader(EyerString _path, EyerAVReaderCustomIO * _customIO = nullptr);
        ~EyerAVReader();

        int Open();
        int OpenInput();
        int FindStreamInfo();

        bool IsOpen();

        int Close();

        double GetDuration();

        int GetStreamCount();
        int GetStream(EyerAVStream & stream, int index);
        EyerAVStream GetStream(int index);

        int GetTimebase(EyerAVRational & timebase, int streamIndex);

        int Seek(double time);
        int SeekStream(int64_t t, int streamId);
        int SeekStream(double t, int streamId);

        int Read(EyerAVPacket & packet);
        int Read(EyerAVPacket * packet);
        EyerSmartPtr<EyerAVPacket> Read(int & ret);

        int GetAudioStreamIndex() const;
        int GetVideoStreamIndex() const;

    private:
        EyerAVReader(const EyerAVReader & reader) = delete;
        EyerAVReader & operator = (const EyerAVReader & reader) = delete;

    public:
        EyerAVReaderPrivate * piml = nullptr;
        EyerAVReaderCustomIO * customIO = nullptr;
    };
}

#endif //EYERLIB_EYERAVREADER_HPP
