#include "EyerAVDecoderLine.hpp"

#include "EyerAVErrorCode.hpp"

#include <math.h>

namespace Eyer
{
    EyerAVDecoderLine::EyerAVDecoderLine(const EyerString & _path, double _startSeekTime, const EyerAVDecoderLineParams & _params)
    {
        params = _params;

        startSeekTime = _startSeekTime;

        reader = new EyerAVReader(_path);
        int ret = reader->Open();
        if(ret){
            EyerLog("EyerAVDecoderLine Open Fail: %s\n", _path.c_str());
            return;
        }

        int videoStreamIndex = reader->GetVideoStreamIndex();
        int audioStreamIndex = reader->GetAudioStreamIndex();

        if(videoStreamIndex < 0){
            EyerLog("EyerAVDecoderLine No Video Stream: %s\n", _path.c_str());
            return;
        }

        currentStreamIndex = videoStreamIndex;

        EyerAVStream videoStream;
        ret = reader->GetStream(videoStream, videoStreamIndex);
        if(ret){
            EyerLog("EyerAVDecoderLine Get Stream Fail: %s\n", _path.c_str());
            return;
        }

        decoder = new EyerAVDecoder();
        ret = decoder->Init(videoStream);
        if(ret){
            EyerLog("EyerAVDecoderLine Decoder Init Fail: %s\n", _path.c_str());
            return;
        }

        if(startSeekTime > 0.0){
            ret = reader->Seek(startSeekTime);
            if(ret){
                ret = reader->Seek(0);
            }
        }
    }
    EyerAVDecoderLine::EyerAVDecoderLine(const EyerString & path, double _startSeekTime)
        : EyerAVDecoderLine(path, _startSeekTime, EyerAVDecoderLineParams())
    {

    }

    EyerAVDecoderLine::~EyerAVDecoderLine()
    {
        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }
        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }
        for(int i=0; i<frameCache.size(); i++){
            delete frameCache[i];
        }
        frameCache.clear();

        if(lastFrame != nullptr){
            delete lastFrame;
            lastFrame = nullptr;
        }
    }

    int EyerAVDecoderLine::GetFrame(EyerAVFrame & frame, double pts)
    {
        if(currentStreamIndex < 0){
            return -1;
        }
        // EyerLog("frameCache size(): %d\n", frameCache.size());
        // EyerLog("GetFrame() pts: %f\n", pts);
        if(pts < GetStartTime()){
            EyerLog("Start Seek Time: %f, GetFrame: %f\n", startSeekTime, pts);
        }

        if(pts < 0.0){
            return EYER_AV_DECODER_LINE_PTS_ERROR;
        }

        while(1){
            int ret = SearchFrameInCache(frame, pts);
            if(ret == EYER_AV_OK){
                return EYER_AV_OK;
            }
            else if(ret == EYER_AV_DECODER_LINE_NOT_MATCH_REGION){
                return EYER_AV_DECODER_LINE_NOT_FIND;
            }
            else if(ret == EYER_AV_DECODER_LINE_NEED_MORE_DATA){
                // 需要更多的数据，要进行解码了x
                // 记录当前缓存有多少帧，
                int canDropFrames = frameCache.size() - 1;
                if(canDropFrames <= 0){
                    canDropFrames = 0;
                }

                ret = DecodeFrame();
                ClearCache(canDropFrames);
                if(ret == EYER_AV_DECODER_LINE_DECODER_END_OF_FILE || ret == EYER_AV_DECODER_LINE_DECODER_ERROR){
                    // 到了文件结尾或者视频出错了。
                    ret = SearchFrameInCache(frame, pts);
                    if(ret == EYER_AV_OK){
                        return EYER_AV_OK;
                    }
                    else if(ret == EYER_AV_DECODER_LINE_NOT_MATCH_REGION){
                        return EYER_AV_DECODER_LINE_NOT_FIND;
                    }
                    else if(ret == EYER_AV_DECODER_LINE_NEED_MORE_DATA){
                        if(frameCache.size() > 0){
                            frame = *frameCache[frameCache.size() - 1];
                            return EYER_AV_OK;
                        }
                        return EYER_AV_DECODER_LINE_NOT_FIND;
                    }
                    else {
                        return EYER_AV_DECODER_LINE_NOT_FIND;
                    }
                }
            }
            else{

            }
        }

        return EYER_AV_DECODER_LINE_NOT_FIND;
    }

    int EyerAVDecoderLine::GetCacheSize()
    {
        return frameCache.size();
    }

    double EyerAVDecoderLine::GetStartTime()
    {
        if(frameCache.size() > 0){
            return frameCache[0]->GetSecPTS();
        }
        return startSeekTime;
    }

    int EyerAVDecoderLine::SearchFrameInCache(EyerAVFrame & frame, double pts)
    {
        for(int i=0;i<frameCache.size();i++){
            double secPTS = frameCache[i]->GetSecPTS();
            if(secPTS == pts){
                frame = *frameCache[i];
                return EYER_AV_OK;
            }
            else if(secPTS < pts){
                continue;
            }
            else{
                if(i <= 0){
                    return EYER_AV_DECODER_LINE_NOT_MATCH_REGION;
                }
                double lastSecPTS = frameCache[i - 1]->GetSecPTS();
                double nowSecPTS  = frameCache[i]->GetSecPTS();

                if(abs(lastSecPTS - pts) >= abs(nowSecPTS - pts)){
                    frame = *frameCache[i];
                    return EYER_AV_OK;
                }
                else{
                    frame = *frameCache[i - 1];
                    return EYER_AV_OK;
                }
            }
        }

        return EYER_AV_DECODER_LINE_NEED_MORE_DATA;
    }

    int EyerAVDecoderLine::DecodeFrame()
    {
        int lastCacheSize = frameCache.size();

        while(1) {
            EyerAVPacket packet;
            int ret = reader->Read(packet);
            if (ret) {
                // 读到了文件末尾或者是出错了
                ret = decoder->SendPacketNull();
                if (ret) {
                    return EYER_AV_DECODER_LINE_DECODER_ERROR;
                }
                while (1) {
                    EyerAVFrame * frame = new EyerAVFrame();
                    ret = decoder->RecvFrame(*frame);
                    if (ret) {
                        delete frame;
                        break;
                    }

                    if(params.isScale) {
                        EyerAVFrame * outframe = new EyerAVFrame();
                        frame->Scale(*outframe, params.pixelFormat, params.scaleWidth, params.scaleHeight);

                        frameCache.push_back(outframe);
                        delete frame;
                    }
                    else{
                        frameCache.push_back(frame);
                    }
                }
                return EYER_AV_DECODER_LINE_DECODER_END_OF_FILE;
            }

            if (currentStreamIndex != packet.GetStreamIndex()) {
                continue;
            }

            ret = decoder->SendPacket(packet);
            if (ret) {
                return EYER_AV_DECODER_LINE_DECODER_ERROR;
            }

            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(*frame);
                if(ret){
                    delete frame;
                    break;
                }

                // EyerLog("Frame.... %lld\n", frame->GetPTS());

                if(params.isScale) {
                    EyerAVFrame * outframe = new EyerAVFrame();
                    frame->Scale(*outframe, params.pixelFormat, params.scaleWidth, params.scaleHeight);

                    frameCache.push_back(outframe);
                    delete frame;
                }
                else{
                    frameCache.push_back(frame);
                }
            }

            int nowCacheSize = frameCache.size();
            if(nowCacheSize != lastCacheSize){
                return EYER_AV_OK;
            }
            continue;
        }
        return EYER_AV_OK;
    }

    int EyerAVDecoderLine::ClearCache(int maxDropFrames)
    {
        int times = 0;
        int maxFrame = params.lineCacheMaxFrame;
        while(1){
            if(GetCacheSize() <= maxFrame){
                break;
            }
            if(times >= maxDropFrames){
                break;
            }

            std::vector<EyerAVFrame *>::iterator itr = frameCache.begin();

            EyerAVFrame * frame = frameCache[0];
            delete frame;

            frameCache.erase(itr);
            times++;
        }
        return 0;
    }
}