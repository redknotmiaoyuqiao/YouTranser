#include "EyerAVSnapshotLine.hpp"

#include "EyerAVErrorCode.hpp"

namespace Eyer
{
    EyerAVSnapshotLine::EyerAVSnapshotLine(const EyerString & _path, const EyerAVStream & _videoStream, int _videoStreamIndex, double _pts, EyerAVReaderCustomIO * _customIO)
        : mPath(_path)
        , mCustomIO(_customIO)
        , mVideoStream(_videoStream)
        , mVideoStreamIndex(_videoStreamIndex)
        , startSeekTime(_pts)
    {
        reader = std::make_shared<EyerAVReader>(mPath, mCustomIO);
        reader->OpenInput();
        reader->Seek(startSeekTime);

        decoder = std::make_shared<EyerAVDecoder>();
        decoder->Init(mVideoStream);
    }

    EyerAVSnapshotLine::~EyerAVSnapshotLine()
    {
        if(reader != nullptr){
            reader->Close();
        }
    }

    int EyerAVSnapshotLine::GetFrame(std::shared_ptr<EyerAVFrame> & frame, double pts)
    {
        if(pts < 0.0) {
            return -1;
        }

        if(mVideoStreamIndex < 0){
            return -1;
        }

        if(pts < GetStartTime()){
            EyerLog("Start Seek Time: %f, GetFrame: %f\n", startSeekTime, pts);
            return -1;
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

                int s = frameCache.size();
                ret = DecodeFrame();
                // EyerLog("Decode: %d\n",frameCache.size() -s );
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
                            frame = frameCache[frameCache.size() - 1];
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

    double EyerAVSnapshotLine::GetStartTime()
    {
        if(frameCache.size() > 0){
            return frameCache[0]->GetSecPTS();
        }
        return startSeekTime;
    }

    int EyerAVSnapshotLine::SearchFrameInCache(std::shared_ptr<EyerAVFrame> & frame, double pts)
    {
        for(int i=0;i<frameCache.size();i++){
            double secPTS = frameCache[i]->GetSecPTS();
            if(secPTS == pts){
                frame = frameCache[i];
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
                    frame = frameCache[i];
                    return EYER_AV_OK;
                }
                else{
                    frame = frameCache[i - 1];
                    return EYER_AV_OK;
                }
            }
        }

        return EYER_AV_DECODER_LINE_NEED_MORE_DATA;
    }


    int EyerAVSnapshotLine::DecodeFrame()
    {
        while(1) {
            if (tempFrameCache.size() > 0) {
                std::shared_ptr<EyerAVFrame> f = tempFrameCache.front();
                tempFrameCache.pop();
                frameCache.push_back(f);
                return EYER_AV_OK;
            } else {
                EyerAVPacket packet;
                int ret = reader->Read(packet);
                if (ret) {
                    ret = decoder->SendPacketNull();
                    if (ret) {
                        return EYER_AV_DECODER_LINE_DECODER_ERROR;
                    }
                    while (1) {
                        std::shared_ptr<EyerAVFrame> frame = std::make_shared<EyerAVFrame>();
                        ret = decoder->RecvFrame(*(frame.get()));
                        if (ret) {
                            break;
                        }

                        tempFrameCache.push(frame);
                    }
                    return EYER_AV_DECODER_LINE_DECODER_END_OF_FILE;
                }

                if (mVideoStreamIndex != packet.GetStreamIndex()) {
                    continue;
                }

                ret = decoder->SendPacket(packet);
                if (ret) {
                    return EYER_AV_DECODER_LINE_DECODER_ERROR;
                }

                while (1) {
                    std::shared_ptr<EyerAVFrame> frame = std::make_shared<EyerAVFrame>();
                    ret = decoder->RecvFrame(*(frame.get()));
                    if (ret) {
                        break;
                    }
                    tempFrameCache.push(frame);
                }
            }
        }
        return EYER_AV_OK;
    }

    int EyerAVSnapshotLine::ClearCache(int maxDropFrames)
    {
        int times = 0;
        int maxFrame = 5;
        while(1){
            if(frameCache.size() <= maxFrame){
                break;
            }
            if(times >= maxDropFrames){
                break;
            }

            std::vector<std::shared_ptr<EyerAVFrame>>::iterator itr = frameCache.begin();
            frameCache.erase(itr);
            times++;
        }
        return 0;
    }
}