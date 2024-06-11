#include "EyerAVSnapshot.hpp"

#include "EyerAVReader.hpp"

namespace Eyer
{
    EyerAVSnapshot::EyerAVSnapshot(const EyerString & _path, EyerAVReaderCustomIO * _customIO)
        : mPath(_path)
        , mCustomIO(_customIO)
    {

    }

    EyerAVSnapshot::~EyerAVSnapshot()
    {

    }

    int EyerAVSnapshot::Init()
    {
        EyerAVReader reader(mPath);
        int ret = reader.Open();
        if(ret){
            EyerLogE("Open file fail, %s\n", mPath.c_str());
            return ret;
        }

        mVideoStreamIndex = reader.GetVideoStreamIndex();
        if(mVideoStreamIndex < 0){
            EyerLogE("No video index, %s\n", mPath.c_str());
            return -2;
        }

        ret = reader.GetStream(mVideoStream, mVideoStreamIndex);
        if(ret){
            EyerLogE("Get video stream fail, %s\n", mPath.c_str());
            return ret;
        }

        return 0;
    }

    std::shared_ptr<EyerAVFrame> EyerAVSnapshot::GetFrame(double pts)
    {
        while(mDecoderLineCache.size() > 2){
            std::shared_ptr<EyerAVSnapshotLine> d = nullptr;
            for(int i=0;i<mDecoderLineCache.size();i++) {
                std::shared_ptr<EyerAVSnapshotLine> decoderLine = mDecoderLineCache[i];
                double startTime = decoderLine->GetStartTime();
                if(d == nullptr){
                    d = decoderLine;
                }
                else{
                    if(abs(pts - d->GetStartTime()) < abs(pts - startTime)){
                        d = decoderLine;
                    }
                }
            }

            for(std::vector<std::shared_ptr<EyerAVSnapshotLine>>::iterator it = mDecoderLineCache.begin(); it != mDecoderLineCache.end();) {
                if (*it == d) {
                    it = mDecoderLineCache.erase(it);
                } else {
                    ++it;
                }
            }
        }

        std::shared_ptr<EyerAVSnapshotLine> decoderLine = FindSnapshotLine(pts);
        if(decoderLine == nullptr){
            decoderLine = std::make_shared<EyerAVSnapshotLine>(mPath, mVideoStream, mVideoStreamIndex, pts, mCustomIO);
            mDecoderLineCache.push_back(decoderLine);
        }

        std::shared_ptr<EyerAVFrame> fff = nullptr;
        decoderLine->GetFrame(fff, pts);
        return fff;
    }

    std::shared_ptr<EyerAVSnapshotLine> EyerAVSnapshot::FindSnapshotLine(double pts)
    {
        std::shared_ptr<EyerAVSnapshotLine> res = nullptr;
        double minDist = 0.0;

        for(int i=0;i<mDecoderLineCache.size();i++) {
            double startTime = mDecoderLineCache[i]->GetStartTime();
            if(pts >= startTime){
                if(res == nullptr){
                    res = mDecoderLineCache[i];
                    minDist = abs(pts - startTime);
                }
                else{
                    if(minDist > abs(pts - startTime)){
                        res = mDecoderLineCache[i];
                        minDist = abs(pts - startTime);
                    }
                }
            }
        }

        if(res != nullptr){
            if(minDist >= 1.0){
                res = nullptr;
            }
        }

        return res;
    }
}