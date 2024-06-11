#include "EyerAVDecoderBox.hpp"

#include <math.h>

namespace Eyer
{
    EyerAVDecoderBox::EyerAVDecoderBox(const EyerString & _path, EyerAVReaderCustomIO * _customIO)
        : EyerAVDecoderBox(_path, EyerAVDecoderLineParams(), _customIO)
    {

    }

    EyerAVDecoderBox::EyerAVDecoderBox(const EyerString & _path, const EyerAVDecoderLineParams & _params, EyerAVReaderCustomIO * _customIO)
    {
        params      = _params;
        path        = _path;
        customIO    = _customIO;
    }

    EyerAVDecoderBox::~EyerAVDecoderBox()
    {
        for(int i=0;i<decoderLineCache.size();i++) {
            delete decoderLineCache[i];
        }
        decoderLineCache.clear();
    }

    double EyerAVDecoderBox::GetDuration()
    {
        return 8.4;
    }

    int EyerAVDecoderBox::GetFrame(EyerAVFrame & frame, double _pts)
    {
        return GetFrameInternal(frame, _pts);
    }

    int EyerAVDecoderBox::GetFrameInternal(EyerAVFrame & frame, double pts)
    {
        while(decoderLineCache.size() > 2){
            EyerAVDecoderLine * d = nullptr;
            for(int i=0;i<decoderLineCache.size();i++) {
                EyerAVDecoderLine * decoderLine = decoderLineCache[i];
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

            for(std::vector<EyerAVDecoderLine *>::iterator it = decoderLineCache.begin(); it != decoderLineCache.end();) {
                if (*it == d) {
                    it = decoderLineCache.erase(it);
                    if(d != nullptr){
                        delete d;
                        d = nullptr;
                    }
                } else {
                    ++it;
                }
            }
        }

        EyerAVDecoderLine * decoderLine = findDecoderLine(pts);
        if(decoderLine == nullptr){
            // EyerLog("Create Decode Line: %f, path: %s\n", pts, path.c_str());
            decoderLine = new EyerAVDecoderLine(path, pts, customIO, params);
            decoderLineCache.push_back(decoderLine);
        }

        return decoderLine->GetFrame(frame, pts);
    }

    EyerAVDecoderLine * EyerAVDecoderBox::findDecoderLine(double pts)
    {
        EyerAVDecoderLine * res = nullptr;
        double minDist = 0.0;

        for(int i=0;i<decoderLineCache.size();i++) {
            double startTime = decoderLineCache[i]->GetStartTime();
            if(pts >= startTime){
                if(res == nullptr){
                    res = decoderLineCache[i];
                    minDist = abs(pts - startTime);
                }
                else{
                    if(minDist > abs(pts - startTime)){
                        res = decoderLineCache[i];
                        minDist = abs(pts - startTime);
                    }
                }
            }
        }

        if(res != nullptr){
            if(minDist >= 2.0){
                // res = nullptr;
            }
        }

        return res;
    }
}