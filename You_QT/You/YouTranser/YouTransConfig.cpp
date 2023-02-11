#include "YouTransConfig.hpp"
#include "ui_YouTransConfig.h"

#include <QDebug>

#include "YouTransAppConfig.hpp"

#include "EyerAVTranscoder/EyerAVTranscoderHeader.hpp"

YouTransConfig::YouTransConfig(const YouTranscoderParams & inputParams, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YouTransConfig)
{
    params = inputParams;

    ui->setupUi(this);

    Eyer::YouTransAppConfig appConfig;
    setWindowTitle(appConfig.Get_TRANS_CONFIG_WINDOWS_TITLE());
    setWindowIcon(QIcon(appConfig.GetLogoPath()));

    ui->config_label_set_avfilefmt->setText(appConfig.Get_TRANS_CONFIG_AVFILEFMT());
    ui->config_label_set_video->setText(appConfig.Get_TRANS_CONFIG_SET_VIDEO());
    ui->config_label_set_audio->setText(appConfig.Get_TRANS_CONFIG_SET_AUDIO());
    ui->config_label_set_other->setText("其他：");

    ui->config_btn_okay->setText(appConfig.Get_TRANS_CONFIG_BUTTON_OK());
    ui->config_btn_cancel->setText(appConfig.Get_TRANS_CONFIG_BUTTON_CANCEL());

    ui->config_videopixfmt_combo_box_label->setText(appConfig.Get_TRANS_CONFIG_PIXELFMT_LABEL());
    ui->config_videocodec_coombo_box_label->setText(appConfig.Get_TRANS_CONFIG_VIDEOCODEC_LABEL());
    ui->config_vcrf_spin_box_label->setText(appConfig.Get_TRANS_CONFIG_CRF_LABEL());

    ui->config_audiocodec_combo_box_label->setText(appConfig.Get_TRANS_CONFIG_AUDIOCODEC_LABEL());
    ui->config_channellayout_combo_box_label->setText(appConfig.Get_TRANS_CONFIG_CHANNEL_LAYOUT_LABEL());
    ui->config_samplerate_combo_box_label->setText(appConfig.Get_TRANS_CONFIG_SAMPLE_RATE_LABEL());

    ui->config_label_set_filename->setText(appConfig.Get_TRANS_CONFIG_SET_FILENAME_LABEL());
    ui->config_filename_label->setText(appConfig.Get_TRAND_CONFIG_FILENAME_LABEL());

    ui->config_decodethread_spin_box_label->setText("解码线程数：");
    ui->config_decodethread_spin_box->setValue(params.GetDecodeThreadNum());
    ui->config_decodethread_spin_box->setMaximum(10);
    ui->config_decodethread_spin_box->setMinimum(1);

    ui->config_encodethread_spin_box_label->setText("编码线程数：");
    ui->config_encodethread_spin_box->setValue(params.GetEncodeThreadNum());
    ui->config_encodethread_spin_box->setMaximum(10);
    ui->config_encodethread_spin_box->setMinimum(1);

    ui->config_transnum_sametime_spin_box_label->setText("同时进行的任务数：");
    ui->config_transnum_sametime_spin_box->setValue(params.GetTransNumSametime());
    ui->config_transnum_sametime_spin_box->setMaximum(10);
    ui->config_transnum_sametime_spin_box->setMinimum(1);

    connect(ui->config_btn_okay,        SIGNAL(clicked()),    this,   SLOT(OkayClickListener()));
    connect(ui->config_btn_cancel,      SIGNAL(clicked()),    this,   SLOT(CancelClickListener()));

    ui->config_avfilefmt_combo_box->clear();

    connect(ui->config_avfilefmt_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onAVFileFmtCurrentIndexChanged(int)), Qt::DirectConnection);
    connect(ui->config_videocodec_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onVideoCodecCurrentIndexChanged(int)), Qt::DirectConnection);
    connect(ui->config_audiocodec_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onAudioCodecCurrentIndexChanged(int)), Qt::DirectConnection);
    connect(ui->config_channellayout_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onChannellayoutCurrentIndexChanged(int)), Qt::DirectConnection);

    Eyer::EyerAVTranscoderSupport transcoderSupport;
    std::vector<Eyer::EyerAVFileFmt> avfileFmts = transcoderSupport.QuerySupportFmt();

    for(int i=0; i<avfileFmts.size(); i++){
        Eyer::EyerAVFileFmt fileFmt = avfileFmts[i];
        ui->config_avfilefmt_combo_box->addItem(QString(fileFmt.GetDesc().c_str()), fileFmt.GetId());
    }

    // Set Current Data
    ui->config_avfilefmt_combo_box->setCurrentIndex(params.GetOutputFileFmt().GetId());

    // CRF
    ui->config_crf_spin_box->setMaximum(51);
    ui->config_crf_spin_box->setMinimum(0);
    ui->config_crf_spin_box->setValue(params.GetCRF());
    connect(ui->config_crf_spin_box, SIGNAL(valueChanged(int)), this, SLOT(onCRFValueChanged(int)));

    SetCurrentData();
}

YouTransConfig::~YouTransConfig()
{
    delete ui;
}

void YouTransConfig::SetCurrentData()
{
    {
        int index = ui->config_avfilefmt_combo_box->findData(params.GetOutputFileFmt().GetId());
        if ( index != -1 ) {
           ui->config_avfilefmt_combo_box->setCurrentIndex(index);
        }
    }
    {
        int index = ui->config_videocodec_combo_box->findData(params.GetVideoCodecId().GetId());
        if ( index != -1 ) {
           ui->config_videocodec_combo_box->setCurrentIndex(index);
        }
    }
    {
        int index = ui->config_videopixfmt_combo_box->findData(params.GetVideoPixelFormat().GetId());
        if ( index != -1 ) {
           ui->config_videopixfmt_combo_box->setCurrentIndex(index);
        }
    }
    {
        ui->config_crf_spin_box->setValue(params.GetCRF());
    }
    {
        int index = ui->config_audiocodec_combo_box->findData(params.GetAudioCodecId().GetId());
        if ( index != -1 ) {
           ui->config_audiocodec_combo_box->setCurrentIndex(index);
        }
    }
    {
        int index = ui->config_channellayout_combo_box->findData(params.GetAudioChannelLayout().GetId());
        if ( index != -1 ) {
           ui->config_channellayout_combo_box->setCurrentIndex(index);
        }
    }
    {
        int index = ui->config_samplerate_combo_box->findData(params.GetSampleRate());
        if ( index != -1 ) {
           ui->config_samplerate_combo_box->setCurrentIndex(index);
        }
    }
    {
        ui->config_filename_edittext->setText(params.GetFilenamePrefix());
    }
}

void YouTransConfig::onCurrentIndexChanged(int index)
{

}

void YouTransConfig::onAVFileFmtCurrentIndexChanged(int index)
{
    int filefmtId = ui->config_avfilefmt_combo_box->currentData().toInt();
    Eyer::EyerAVFileFmt fmt = Eyer::EyerAVFileFmt::GetAVFileFmtById(filefmtId);

    Eyer::EyerAVTranscoderSupport transcoderSupport;
    std::vector<Eyer::EyerAVCodecID> videoCodecs = transcoderSupport.QuerySupportVideoCodec(fmt);

    ui->config_videocodec_combo_box->clear();
    for(int i=0;i<videoCodecs.size();i++){
        Eyer::EyerAVCodecID codec = videoCodecs[i];
        ui->config_videocodec_combo_box->addItem(codec.GetDescName().c_str(), codec.GetId());
    }

    {
        onVideoCodecCurrentIndexChanged(0);
    }

    std::vector<Eyer::EyerAVCodecID> audioCodecs = transcoderSupport.QuerySupportAudioCodec(fmt);
    ui->config_audiocodec_combo_box->clear();
    for(int i=0;i<audioCodecs.size();i++){
        Eyer::EyerAVCodecID codec = audioCodecs[i];
        ui->config_audiocodec_combo_box->addItem(codec.GetDescName().c_str(), codec.GetId());
    }

    {
        onAudioCodecCurrentIndexChanged(0);
    }
}

void YouTransConfig::onVideoCodecCurrentIndexChanged(int index)
{
    qDebug() << index << Qt::endl;
    int codecId = ui->config_videocodec_combo_box->currentData().toInt();
    Eyer::EyerAVCodecID videoCodec = Eyer::EyerAVCodecID::GetCodecIdById(codecId);

    Eyer::EyerAVTranscoderSupport transcoderSupport;
    std::vector<Eyer::EyerAVPixelFormat> pixelFmts = transcoderSupport.QuerySupportPixelFormat(videoCodec);

    ui->config_videopixfmt_combo_box->clear();
    for(int i=0;i<pixelFmts.size();i++){
        Eyer::EyerAVPixelFormat pixelFmt = pixelFmts[i];
        ui->config_videopixfmt_combo_box->addItem(pixelFmt.GetDescName().c_str(), pixelFmt.GetId());
    }
}

void YouTransConfig::onAudioCodecCurrentIndexChanged(int index)
{
    int codecId = ui->config_audiocodec_combo_box->currentData().toInt();
    Eyer::EyerAVCodecID audioCodec = Eyer::EyerAVCodecID::GetCodecIdById(codecId);

    Eyer::EyerAVTranscoderSupport transcoderSupport;
    std::vector<Eyer::EyerAVChannelLayout> channelLayouts = transcoderSupport.QuerySupportChannelLayout(audioCodec);

    ui->config_channellayout_combo_box->clear();
    for(int i=0;i<channelLayouts.size();i++){
        Eyer::EyerAVChannelLayout channelLayout = channelLayouts[i];
        int channels = Eyer::EyerAVChannelLayout::GetChannelLayoutNBChannels(channelLayout);
        if(channelLayout == Eyer::EyerAVChannelLayout::EYER_KEEP_SAME){
            ui->config_channellayout_combo_box->addItem("和原视频保持一致", channelLayout.GetId());
        }
        else{
            ui->config_channellayout_combo_box->addItem(QString("(声道:") + QString::number(channels) + "）  " + QString(channelLayout.GetDescName().c_str()), channelLayout.GetId());
        }
    }

    ui->config_samplerate_combo_box->clear();
    std::vector<int> sampleRates = transcoderSupport.QuerySupportSampleRate(audioCodec);
    for(int i=0;i<sampleRates.size();i++){
        int sampleRate = sampleRates[i];
        if(sampleRate == -2){
            ui->config_samplerate_combo_box->addItem("和原视频保持一致", sampleRate);
        }
        else {
            ui->config_samplerate_combo_box->addItem(QString("") + QString::number(sampleRate) + " Hz", sampleRate);
        }
    }
}

void YouTransConfig::onChannellayoutCurrentIndexChanged(int index)
{

}

void YouTransConfig::onCRFValueChanged(int value)
{
    QString alert = "";
    if(value >= 0 && value < 18){
        alert = "very good";
    }
    else if(value >= 18 && value < 23){
        alert = "good";
    }
    else if(value >= 23 && value < 28){
        alert = "so so";
    }
    else{
        alert = "bad";
    }

    Eyer::YouTransAppConfig appConfig;
    ui->config_vcrf_spin_box_label->setText(appConfig.Get_TRANS_CONFIG_CRF_LABEL() + alert);
}

void YouTransConfig::closeEvent(QCloseEvent *event)
{
    qDebug() << "YouTransConfig closeEvent" << Qt::endl;
}

void YouTransConfig::OkayClickListener()
{
    // AVFile fmt
    int fmtId = ui->config_avfilefmt_combo_box->currentData().toInt();
    Eyer::EyerAVFileFmt avfileFmt = Eyer::EyerAVFileFmt::GetAVFileFmtById(fmtId);
    params.SetOutputFileFmt(avfileFmt);
    qDebug() << avfileFmt.GetDesc().c_str() << Qt::endl;

    // Video Codec
    int videoCodecId = ui->config_videocodec_combo_box->currentData().toInt();
    Eyer::EyerAVCodecID videoCodec = Eyer::EyerAVCodecID::GetCodecIdById(videoCodecId);
    params.SetVideoCodecId(videoCodec);
    qDebug() << videoCodec.GetDescName().c_str() << Qt::endl;

    // Video Pixel Fmt
    int pixelFmtId = ui->config_videopixfmt_combo_box->currentData().toInt();
    Eyer::EyerAVPixelFormat pixelFmt = Eyer::EyerAVPixelFormat::GetById(pixelFmtId);
    params.SetVideoPixelFormat(pixelFmt);
    qDebug() << pixelFmt.GetDescName().c_str() << Qt::endl;

    // CRF
    int crf = ui->config_crf_spin_box->value();
    params.SetCRF(crf);

    // Audio Codec
    int audioCodecId = ui->config_audiocodec_combo_box->currentData().toInt();
    Eyer::EyerAVCodecID audioCodec = Eyer::EyerAVCodecID::GetCodecIdById(audioCodecId);
    params.SetAudioCodecId(audioCodec);
    qDebug() << audioCodec.GetDescName().c_str() << Qt::endl;

    // Channel Layout
    int channellayoutId = ui->config_channellayout_combo_box->currentData().toInt();
    Eyer::EyerAVChannelLayout audioChannelLayout = Eyer::EyerAVChannelLayout::GetById(channellayoutId);
    params.SetChannelLayout(audioChannelLayout);
    qDebug() << audioChannelLayout.GetDescName().c_str() << Qt::endl;

    // Sample Rate
    int sampleRate = ui->config_samplerate_combo_box->currentData().toInt();
    params.SetSampleRate(sampleRate);

    // Filename Prefix
    QString filenamePrefix = ui->config_filename_edittext->toPlainText();
    filenamePrefix = filenamePrefix.simplified();
    params.SetFilenamePrefix(filenamePrefix);

    int decodethreadNum = ui->config_decodethread_spin_box->value();
    params.SetDecodeThreadNum(decodethreadNum);

    int encodethreadNum = ui->config_encodethread_spin_box->value();
    params.SetEncodeThreadNum(encodethreadNum);

    int transnumSametime = ui->config_transnum_sametime_spin_box->value();
    params.SetTransNumSametime(transnumSametime);

    emit OnConfigWindowsClose();
    close();
}

void YouTransConfig::CancelClickListener()
{
    close();
}

YouTranscoderParams YouTransConfig::GetTranscodeParams()
{
    return params;
}
