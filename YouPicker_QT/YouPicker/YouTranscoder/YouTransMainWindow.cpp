#include "YouTransMainWindow.hpp"
#include "ui_YouTransMainWindow.h"

#include "YouTransAppConfig.hpp"
#include "YouTransConfig.hpp"
#include "YouTransAboutWindow.hpp"

#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QToolBar>
#include <QMenuBar>

YouTransMainWindow::YouTransMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YouTransMainWindow)
{
    ui->setupUi(this);

    // Tool Bar
    QMenuBar * mainMenuBar = menuBar();

    QMenu * menuHelp = mainMenuBar->addMenu("帮助");

    QAction * actionAbout = menuHelp->addAction("关于");
    connect(actionAbout,      SIGNAL(triggered()),    this,   SLOT(AboutActionClickListener()));

    Eyer::YouTransAppConfig config;
    setWindowTitle(config.GetAppName());
    setWindowIcon(QIcon(config.GetLogoPath()));
    ui->btn_set_input_path->setText(config.Get_TRANS_MAIN_BUTTON_SET_INPUT_PATH());
    ui->btn_set_output_path->setText(config.Get_TRANS_MAIN_BUTTON_SET_OUTPUT_PATH());
    ui->btn_start_stop_transcode->setText(config.Get_TRANS_MAIN_BUTTON_START_TRANS_CODE());
    ui->btn_transcode_config->setText(config.Get_TRANS_MAIN_BUTTON_START_SETTING_CONFIG());

    ui->params_key_videocodec->setText("视频编码：");
    ui->params_key_pixelfmt->setText("图像格式：");
    ui->params_key_videocrf->setText("图像质量(CRF)：");

    ui->params_key_audiocodec->setText("音频编码：");
    ui->params_key_audiochannellayout->setText("声道布局：");
    ui->params_key_audiosamplerate->setText("采样率：");

    ui->params_key_decodethreadnum->setText("解码线程数：");
    ui->params_key_encodethreadnum->setText("编码线程数：");
    ui->params_key_transsametime->setText("同时进行任务数：");

    UpdateSystemLabel();

    connect(ui->btn_set_input_path,       SIGNAL(clicked()),    this,   SLOT(SetInputPathClickListener()));
    connect(ui->btn_set_output_path,      SIGNAL(clicked()),    this,   SLOT(SetOutputPathClickListener()));
    connect(ui->btn_transcode_config,     SIGNAL(clicked()),    this,   SLOT(StartTranscodeConfigClickListener()));
    connect(ui->btn_start_stop_transcode, SIGNAL(clicked()),    this,   SLOT(StartTranscodeClickListener()));

    // Config
    QSettings setting(config.GetCompanyName(), config.GetAppId());
    QString transParamsJson = setting.value("TRANS_PARAMS_JSON", "").toString();
    EyerLog("\n%s\n", transParamsJson.toStdString().c_str());

    params.ParseJson(transParamsJson);

    transParamsJson = params.ToJson();
    setting.setValue("TRANS_PARAMS_JSON", transParamsJson);

    ShowTranscoderParams();
}

YouTransMainWindow::~YouTransMainWindow()
{
    if(configWindow != nullptr){
        delete configWindow;
        configWindow = nullptr;
    }

    delete ui;
}

void YouTransMainWindow::closeEvent(QCloseEvent * event)
{
    EyerLog("YouTransMainWindow Close\n");
    int choose = QMessageBox::question(this, tr("退出？"), tr("如果退出，正在转码的视频将会被取消。"), QMessageBox::Yes | QMessageBox::No);

    if(choose == QMessageBox::No) {
        event->ignore();
    }
    else if(choose == QMessageBox::Yes){
        for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
            QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
            TaskItem *taskitem = (TaskItem *) child->widget();
            taskitem->StopTask();
        }
        event->accept();
    }
}

void YouTransMainWindow::SetInputPathClickListener()
{
    QStringList filelist = QFileDialog::getOpenFileNames(this, tr("选择输出文件"));
    for(QString file : filelist){
        // 检查重复文件

        TaskItem * taskitem = new TaskItem(file, this);
        connect(taskitem,       SIGNAL(TaskItem_OnTaskSuccess()),           this,   SLOT(TaskItem_OnTaskSuccess()));
        connect(taskitem,       SIGNAL(TaskItem_OnTaskFail(int)),           this,   SLOT(TaskItem_OnTaskFail(int)));
        connect(taskitem,       SIGNAL(TaskItem_OnRemove(TaskItem *)),      this,   SLOT(TaskItem_OnRemove(TaskItem *)));
        ui->task_list_content_layout->addWidget(taskitem);
    }
}

void YouTransMainWindow::SetOutputPathClickListener()
{
    QString outDir = QFileDialog::getExistingDirectory(this, tr("选择输出文件夹"), params.GetOutputDir());
    if(!outDir.isEmpty()){
        params.SetOutputDir(outDir);
        QString transParamsJson = params.ToJson();

        Eyer::YouTransAppConfig config;
        QSettings setting(config.GetCompanyName(), config.GetAppId());
        setting.setValue("TRANS_PARAMS_JSON", transParamsJson);
        ShowTranscoderParams();
    }
}

void YouTransMainWindow::StartTranscodeConfigClickListener()
{
    if(configWindow != nullptr){
        delete configWindow;
        configWindow = nullptr;
    }
    configWindow = new YouTransConfig(params, this);
    connect(configWindow,                 SIGNAL(OnConfigWindowsClose()),    this,   SLOT(OnConfigWindowsClose()));
    configWindow->setAttribute(Qt::WA_ShowModal, true);
    configWindow->show();
}

void YouTransMainWindow::OnConfigWindowsClose()
{
    params = configWindow->GetTranscodeParams();
    QString transParamsJson = params.ToJson();

    Eyer::YouTransAppConfig config;
    QSettings setting(config.GetCompanyName(), config.GetAppId());
    setting.setValue("TRANS_PARAMS_JSON", transParamsJson);
    ShowTranscoderParams();
}

void YouTransMainWindow::ShowTranscoderParams()
{
    ui->params_val_videocodec->setText(params.GetVideoCodecId().GetDescName().c_str());
    ui->params_val_pixelfmt->setText(params.GetVideoPixelFormat().GetDescName().c_str());
    ui->params_val_videocrf->setText(Eyer::EyerString::Number(params.GetCRF()).c_str());

    ui->params_val_audiocodec->setText(params.GetAudioCodecId().GetDescName().c_str());

    if(params.GetAudioChannelLayout() == Eyer::EyerAVChannelLayout::EYER_KEEP_SAME){
        ui->params_val_audiochannellayout->setText("和原视频保持一致");
    }
    else {
        ui->params_val_audiochannellayout->setText(QString(params.GetAudioChannelLayout().GetDescName().c_str()) + " (声道：" + QString::number(Eyer::EyerAVChannelLayout::GetChannelLayoutNBChannels(params.GetAudioChannelLayout())) +  ")");
    }

    if(params.GetSampleRate() == -2){
        ui->params_val_audiosamplerate->setText("和原视频保持一致");
    }
    else {
        ui->params_val_audiosamplerate->setText(Eyer::EyerString::Number(params.GetSampleRate()).c_str());
    }

    ui->params_val_decodethreadnum->setText(Eyer::EyerString::Number(params.GetDecodeThreadNum()).c_str());
    ui->params_val_encodethreadnum->setText(Eyer::EyerString::Number(params.GetEncodeThreadNum()).c_str());
    ui->params_val_transsametime->setText(Eyer::EyerString::Number(params.GetTransNumSametime()).c_str());

    ui->params_val_output_path->setText(params.GetOutputDir() + "/" + params.GetFilenamePrefix());

    ui->params_val_output_filefmt_label->setText(QString("输出文件格式：") + params.GetOutputFileFmt().GetDesc().c_str());
}

void YouTransMainWindow::StartTranscodeClickListener()
{
    for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
        QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
        TaskItem *taskitem = (TaskItem *) child->widget();
        if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::FAIL) {
            taskitem->SetStatus(Eyer::EyerAVTranscoderStatus::PREPARE);
            taskitem->showStatus();
        }
    }
    StartTranscodeClickListenerInternal();
}

void YouTransMainWindow::StartTranscodeClickListenerInternal()
{
    if(params.GetOutputDir().isEmpty()){
        QMessageBox::critical(this, tr("危险弹窗"), tr("请先设置输出路径"));
        return;
    }
    if(ui->task_list_content_layout->count() <= 0){
        QMessageBox::critical(this, tr("危险弹窗"), tr("无任务"));
        return;
    }

    while(1) {
        int ingCount = 0;
        for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
            QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
            TaskItem *taskitem = (TaskItem *) child->widget();
            if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::ING) {
                ingCount++;
            }
        }

        int prepareCount = 0;
        for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
            QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
            TaskItem *taskitem = (TaskItem *) child->widget();
            if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::PREPARE) {
                prepareCount++;
            }
        }

        int failCount = 0;
        for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
            QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
            TaskItem *taskitem = (TaskItem *) child->widget();
            if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::FAIL) {
                failCount++;
            }
        }

        EyerLog("ingCount: %d, prepareCount: %d, failCount: %d\n", ingCount, prepareCount, failCount);

        if(prepareCount <= 0){
            break;
        }

        if(ingCount >= params.GetTransNumSametime()){
            break;
        }

        for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
            QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
            TaskItem *taskitem = (TaskItem *) child->widget();
            if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::PREPARE) {
                taskitem->SetParams(params);
                taskitem->SetOutputDir(params.GetOutputDir());
                taskitem->SetFilenamePrefix(params.GetFilenamePrefix());
                taskitem->StartTask();
                break;
            }
        }
    }

    UpdateSystemLabel();
}

void YouTransMainWindow::TaskItem_OnTaskSuccess()
{
    StartTranscodeClickListenerInternal();
}

void YouTransMainWindow::TaskItem_OnTaskFail(int code)
{
    StartTranscodeClickListenerInternal();
}

void YouTransMainWindow::TaskItem_OnRemove(TaskItem * taskitem)
{
    taskitem->StopTask();
    ui->task_list_content_layout->removeWidget(taskitem);
    taskitem->setParent(nullptr);
}

int YouTransMainWindow::UpdateSystemLabel()
{
    int taskOunt = ui->task_list_content_layout->count();
    int ingCount = 0;
    for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
        QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
        TaskItem *taskitem = (TaskItem *) child->widget();
        if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::ING) {
            ingCount++;
        }
    }
    int failCount = 0;
    for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
        QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
        TaskItem *taskitem = (TaskItem *) child->widget();
        if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::FAIL) {
            failCount++;
        }
    }
    int succCount = 0;
    for (int i = 0; i < ui->task_list_content_layout->count(); i++) {
        QLayoutItem *child = ui->task_list_content_layout->itemAt(i);
        TaskItem *taskitem = (TaskItem *) child->widget();
        if (taskitem->GetStatus() == Eyer::EyerAVTranscoderStatus::SUCC) {
            succCount++;
        }
    }
    ui->system_status_label->setText("任务总数：" + QString::number(taskOunt) +
                                     " 成功：" + QString::number(succCount) +
                                     " 失败：" + QString::number(failCount));
    return 0;
}

void YouTransMainWindow::AboutActionClickListener()
{
    YouTransAboutWindow * about = new YouTransAboutWindow(this);
    about->show();
}
