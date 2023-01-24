#ifndef EYERLIB_EYERAVREADERVPXALPHATEST_HPP
#define EYERLIB_EYERAVREADERVPXALPHATEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVReaderVPXAlphaTest)
{
    for(int i=0;i<10;i++) {
        Eyer::EyerAVReader reader("/Users/bytedance/Downloads/transparent-video.webm");
        // Eyer::EyerAVReader reader("/Users/bytedance/Movies/2022-06-28 13-22-18.mkv");
        int ret = reader.Open();
        ASSERT_EQ(ret, 0) << "EyerAVReader Open Error\n";
        if (ret) {
            return;
        }

        int streamCount = reader.GetStreamCount();
        EyerLog("Stream Count: %d\n", streamCount);

        std::vector<Eyer::EyerAVDecoder *> decoderList;
        std::vector<Eyer::EyerAVStream *> streamList;
        for (int i = 0; i < streamCount; i++) {
            Eyer::EyerAVStream *stream = new Eyer::EyerAVStream();
            reader.GetStream(*stream, i);
            streamList.push_back(stream);

            Eyer::EyerAVDecoder *decoder = new Eyer::EyerAVDecoder();
            ret = decoder->Init(*stream);
            if (ret) {
                EyerLog("AVDecoder Init Error\n");
            }
            decoderList.push_back(decoder);
        }

        double duration = reader.GetDuration();
        EyerLog("Duration: %.2f s\n", duration);

        int pts = Eyer::EyerRand::Rand(5000);
        double ppp = pts / 1000.0;
        // EyerLog("ppp: %f\n", ppp);
        reader.Seek(ppp);



        int index = 0;
        while (1) {
            Eyer::EyerAVPacket packet;
            ret = reader.Read(packet);
            if (ret) {
                break;
            }
            // EyerLog("packet secPTS: %f \n", packet.GetSecPTS());

            int streamIndex = packet.GetStreamIndex();
            Eyer::EyerAVDecoder *decoder = decoderList[streamIndex];

            // EyerLog("packet: %lld\n", packet.GetPTS());
            ret = decoder->SendPacket(packet);
            if (ret) {
                continue;
            }

            while (1) {
                Eyer::EyerAVFrame frame;
                ret = decoder->RecvFrame(frame);
                if (ret) {
                    break;
                }
                // EyerLog("width: %d, height: %d, pts: %lld, secPts: %f\n", frame.GetWidth(), frame.GetHeight(), frame.GetPTS(), frame.GetSecPTS());
                // EyerLog("PixelFormat: %s\n", frame.GetPixelFormat().GetName().c_str());
            }

            if (index >= 10) {
                // break;
            }
            index++;
        }

        for (int i = 0; i < decoderList.size(); i++) {
            Eyer::EyerAVDecoder *decoder = decoderList[i];
            decoder->SendPacketNull();
            while (1) {
                Eyer::EyerAVFrame frame;
                ret = decoder->RecvFrame(frame);
                if (ret) {
                    break;
                }
                EyerLog("width: %d, height: %d, pts: %lld, secPts: %f\n", frame.GetWidth(), frame.GetHeight(),
                        frame.GetPTS(), frame.GetSecPTS());
            }
        }

        for (int i = 0; i < streamList.size(); i++) {
            delete streamList[i];
        }
        streamList.clear();

        for (int i = 0; i < decoderList.size(); i++) {
            delete decoderList[i];
        }
        decoderList.clear();

        ret = reader.Close();
        ASSERT_EQ(ret, 0) << "EyerAVReader Close Error\n";
        if (ret) {
            return;
        }
    }
}

#endif //EYERLIB_EYERAVREADERVPXALPHATEST_HPP
