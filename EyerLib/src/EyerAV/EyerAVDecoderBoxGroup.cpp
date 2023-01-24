#include "EyerAVDecoderBoxGroup.hpp"

#include "EyerAVDecoderBox.hpp"

namespace Eyer
{
    EyerAVDecoderBoxGroup::EyerAVDecoderBoxGroup(const EyerAVDecoderLineParams & _params)
    {
        params = _params;
    }

    EyerAVDecoderBoxGroup::~EyerAVDecoderBoxGroup()
    {
        /* TODO Add Fucking Free Code */
        std::map<EyerString, EyerAVDecoderBox *>::iterator it;
        for(it = decoderBoxCache.begin(); it != decoderBoxCache.end(); ) {
            delete it->second;
            decoderBoxCache.erase(it++);
        }
    }

    int EyerAVDecoderBoxGroup::GetFrame(EyerAVFrame & frame, const EyerString & path, double pts)
    {
        EyerAVDecoderBox * decoderBox = FindDecoderBox(path);
        if(decoderBox == nullptr){
            return -1;
        }

        int ret = decoderBox->GetFrame(frame, pts);

        return ret;
    }

    EyerAVDecoderBox * EyerAVDecoderBoxGroup::FindDecoderBox(const EyerString & path)
    {
        EyerAVDecoderBox * decoderBox = nullptr;

        std::map<EyerString, EyerAVDecoderBox *>::iterator it = decoderBoxCache.find(path);
        if (it != decoderBoxCache.end()){
            // 找到了
            decoderBox = it->second;
        }
        else {
            // 没找到
            decoderBox = new EyerAVDecoderBox(path, params);
            decoderBoxCache.insert(std::map<EyerString, EyerAVDecoderBox *>::value_type(path, decoderBox));
        }

        return decoderBox;
    }
}