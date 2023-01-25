#include "YouTranscoderParams.hpp"

#include "EyerCore/EyerCore.hpp"

YouTranscoderParams::YouTranscoderParams()
{

}

YouTranscoderParams::~YouTranscoderParams()
{

}

YouTranscoderParams::YouTranscoderParams(const YouTranscoderParams & params)
{
    *this = params;
}

YouTranscoderParams & YouTranscoderParams::operator = (const YouTranscoderParams & params)
{
    Eyer::EyerAVTranscoderParams::operator = (params);
    filenamePrefix      = params.filenamePrefix;
    transNumSametime    = params.transNumSametime;
    outputDir           = params.outputDir;
    return *this;
}

int YouTranscoderParams::ParseJson(const QString & jsonStr)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsonStr.toUtf8(), &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        if (doucment.isObject())  {
            QJsonObject object = doucment.object();
            if (object.contains("eyer_lib_version")) {
                QJsonValue value = object.value("eyer_lib_version");
                if(value.isString()){
                    QString eyer_lib_version_str = value.toString();
                    QString currentVersion(Eyer::EyerVersion::GetEyerLibVersion().c_str());
                    if(eyer_lib_version_str != currentVersion){
                        EyerLog("Give up!");
                        return -1;
                    }
                }
                else {
                    return -1;
                }
            }
            else {
                return -1;
            }

            // output_file_fmt

            if (object.contains("output_file_fmt")) {
                QJsonValue value = object.value("output_file_fmt");
                int avFileFmtId = value.toInt(Eyer::EyerAVFileFmt::MP4.GetId());
                Eyer::EyerAVFileFmt fmt = Eyer::EyerAVFileFmt::GetAVFileFmtById(avFileFmtId);
                EyerLog("AV File fmt: %s\n", fmt.GetDesc().c_str());
                SetOutputFileFmt(fmt);
            }

            if (object.contains("video_codec")) {
                QJsonValue value = object.value("video_codec");
                int codecID = value.toInt(Eyer::EyerAVCodecID::CODEC_ID_H264.GetId());
                Eyer::EyerAVCodecID codec = Eyer::EyerAVCodecID::GetCodecIdById(codecID);
                EyerLog("Video Codec ID: %s\n", codec.GetDescName().c_str());
                SetVideoCodecId(codec);
            }
            if (object.contains("pixel_format")) {
                QJsonValue value = object.value("pixel_format");
                int pixelfmtID = value.toInt(Eyer::EyerAVPixelFormat::EYER_YUV420P.GetId());
                Eyer::EyerAVPixelFormat pixelfmt = Eyer::EyerAVPixelFormat::GetById(pixelfmtID);
                EyerLog("Pixel Format: %s\n", pixelfmt.GetDescName().c_str());
                SetVideoPixelFormat(pixelfmt);
            }
            if (object.contains("video_crf")) {
                QJsonValue value = object.value("video_crf");
                int crf = value.toInt(18);
                EyerLog("CRF: %d\n", crf);
                SetCRF(crf);
            }


            if (object.contains("audio_codec")) {
                QJsonValue value = object.value("audio_codec");
                int codecID = value.toInt(Eyer::EyerAVCodecID::CODEC_ID_MP3.GetId());
                Eyer::EyerAVCodecID codec = Eyer::EyerAVCodecID::GetCodecIdById(codecID);
                EyerLog("Audio Codec ID: %s\n", codec.GetDescName().c_str());
                SetAudioCodecId(codec);
            }
            if (object.contains("audio_channel_layout")) {
                QJsonValue value = object.value("audio_channel_layout");
                int channelLayoutID = value.toInt(Eyer::EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO.GetId());
                Eyer::EyerAVChannelLayout channelLayout = Eyer::EyerAVChannelLayout::GetById(channelLayoutID);
                EyerLog("Channel Layout: %s\n", channelLayout.GetDescName().c_str());
                SetChannelLayout(channelLayout);
            }
            if (object.contains("audio_sample_rate")) {
                QJsonValue value = object.value("audio_sample_rate");
                int sampleRate = value.toInt(44100);
                EyerLog("Sample Rate: %d\n", sampleRate);
                SetSampleRate(sampleRate);
            }


            if (object.contains("filename_prefix")) {
                QJsonValue value = object.value("filename_prefix");
                QString filenamePrefix = value.toString();
                EyerLog("Filename Prefix: %s\n", filenamePrefix.toStdString().c_str());
                SetFilenamePrefix(filenamePrefix);
            }



            if (object.contains("decode_thread_num")) {
                QJsonValue value = object.value("decode_thread_num");
                EyerLog("decode_thread_num: %d\n", value.toInt(4));
                SetDecodeThreadNum(value.toInt(4));
            }
            if (object.contains("encode_thread_num")) {
                QJsonValue value = object.value("encode_thread_num");
                EyerLog("encode_thread_num: %d\n", value.toInt(4));
                SetDecodeThreadNum(value.toInt(4));
            }

            if (object.contains("trans_num_sametime")) {
                QJsonValue value = object.value("trans_num_sametime");
                EyerLog("trans_num_sametime: %d\n", value.toInt(4));
                SetTransNumSametime(value.toInt(2));
            }


            if (object.contains("output_dir")) {
                QJsonValue value = object.value("output_dir");
                QString outputDir = value.toString();
                SetOutputDir(outputDir);
            }
        }
    }
    return 0;
}

QString YouTranscoderParams::ToJson()
{
    QJsonObject jsonObj;
    jsonObj.insert("eyer_lib_version", Eyer::EyerVersion::GetEyerLibVersion().c_str());

    jsonObj.insert("output_file_fmt", GetOutputFileFmt().GetId());
    jsonObj.insert("output_file_fmt_desc", GetOutputFileFmt().GetDesc().c_str());

    jsonObj.insert("video_codec", GetVideoCodecId().GetId());
    jsonObj.insert("video_codec_desc", GetVideoCodecId().GetDescName().c_str());

    jsonObj.insert("pixel_format", GetVideoPixelFormat().GetId());
    jsonObj.insert("pixel_format_desc", GetVideoPixelFormat().GetDescName().c_str());

    jsonObj.insert("video_crf", GetCRF());

    jsonObj.insert("audio_codec", GetAudioCodecId().GetId());
    jsonObj.insert("audio_codec_desc", GetAudioCodecId().GetDescName().c_str());

    jsonObj.insert("audio_channel_layout", GetAudioChannelLayout().GetId());
    jsonObj.insert("audio_channel_layout_desc", GetAudioChannelLayout().GetDescName().c_str());

    jsonObj.insert("audio_sample_rate", GetSampleRate());

    jsonObj.insert("filename_prefix", GetFilenamePrefix());

    jsonObj.insert("decode_thread_num", GetDecodeThreadNum());
    jsonObj.insert("encode_thread_num", GetEncodeThreadNum());

    jsonObj.insert("trans_num_sametime", GetTransNumSametime());

    jsonObj.insert("trans_num_sametime", GetTransNumSametime());

    jsonObj.insert("output_dir", GetOutputDir());

    QJsonDocument doc(jsonObj);
    return doc.toJson();
}

QString YouTranscoderParams::GetFilenamePrefix()
{
    return filenamePrefix;
}

int YouTranscoderParams::SetFilenamePrefix(const QString & _filenamePrefix)
{
    filenamePrefix = _filenamePrefix;
    return 0;
}

const int YouTranscoderParams::GetTransNumSametime() const
{
    return transNumSametime;
}

int YouTranscoderParams::SetTransNumSametime(int num)
{
    transNumSametime = num;
    return 0;
}

QString YouTranscoderParams::GetOutputDir() const
{
    return outputDir;
}

int YouTranscoderParams::SetOutputDir(const QString & dir)
{
    outputDir = dir;
    return 0;
}
