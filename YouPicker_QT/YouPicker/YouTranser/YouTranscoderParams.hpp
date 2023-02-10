#ifndef YOUTRANSCODERPARAMS_HPP
#define YOUTRANSCODERPARAMS_HPP

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

#include "EyerAVTranscoder/EyerAVTranscoderHeader.hpp"

class YouTranscoderParams : public Eyer::EyerAVTranscoderParams
{
public:
    YouTranscoderParams();
    ~YouTranscoderParams();

    YouTranscoderParams(const YouTranscoderParams & params);
    YouTranscoderParams & operator = (const YouTranscoderParams & params);

    QString ToJson();
    int ParseJson(const QString & jsonStr);


    QString GetFilenamePrefix();
    int SetFilenamePrefix(const QString & _filenamePrefix);

    const int GetTransNumSametime() const;
    int SetTransNumSametime(int num);

    QString GetOutputDir() const;
    int SetOutputDir(const QString & dir);
private:
    QString filenamePrefix = "${origin_file_name}_${output_video_codec}_${video_pixelfmt}_${output_audio_codec}";
    QString outputDir = "";
    int transNumSametime = 2;
};

#endif // YOUTRANSCODERPARAMS_HPP
