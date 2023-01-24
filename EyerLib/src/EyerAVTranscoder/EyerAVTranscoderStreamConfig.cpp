#include "EyerAVTranscoderStreamConfig.hpp"

namespace Eyer
{
    EyerAVTranscoderStreamConfig::EyerAVTranscoderStreamConfig()
    {

    }

    EyerAVTranscoderStreamConfig::~EyerAVTranscoderStreamConfig()
    {

    }

    EyerAVTranscoderStreamConfig::EyerAVTranscoderStreamConfig(const EyerAVTranscoderStreamConfig & streamConfig)
    {
        *this = streamConfig;
    }

    EyerAVTranscoderStreamConfig & EyerAVTranscoderStreamConfig::operator = (const EyerAVTranscoderStreamConfig & streamConfig)
    {
        streamType = streamConfig.streamType;
        codecId = streamConfig.codecId;
        return *this;
    }
}