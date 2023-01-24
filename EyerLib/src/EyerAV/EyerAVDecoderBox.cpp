#include "EyerAVDecoderBox.hpp"

#include <math.h>

namespace Eyer
{
    EyerAVDecoderBox::EyerAVDecoderBox(const EyerString & _path)
        : EyerAVDecoderBox(_path, EyerAVDecoderLineParams())
    {

    }

    EyerAVDecoderBox::EyerAVDecoderBox(const EyerString & _path, const EyerAVDecoderLineParams & _params)
    {
        params  = _params;
        path    = _path;
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

    int EyerAVDecoderBox::GetFrame(EyerAVFrame & frame, double pts)
    {
        while(decoderLineCache.size() > 5){
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
            decoderLine = new EyerAVDecoderLine(path, pts, params);
            decoderLineCache.push_back(decoderLine);
        }

        return decoderLine->GetFrame(frame, pts);
    }

    EyerAVDecoderLine * EyerAVDecoderBox::findDecoderLine(double pts)
    {
        // EyerLog("Size: %d\n", decoderLineCache.size());
        EyerAVDecoderLine * res = nullptr;
        int minDist = -1;

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

        return res;
    }
}