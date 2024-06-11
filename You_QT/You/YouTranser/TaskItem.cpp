#include "TaskItem.hpp"
#include "ui_TaskItem.h"

#include <QFileInfo>

TaskItem::TaskItem(QString inputPath, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskItem)
    , taskThread(inputPath)
{
    ui->setupUi(this);

    ui->task_progress_bar->setMaximum(100);
    ui->task_progress_bar->setValue(0);

    ui->task_input_path->setText(inputPath);

    ui->task_btn_remove->setText("移除任务");
    connect(ui->task_btn_remove,       SIGNAL(clicked()),    this,   SLOT(OnBtnRemove()));

#ifndef WIN32
    ui->task_progress_label->setText("0%");
#else
    ui->task_progress_label->setText("");
#endif

    ui->task_error_label->setText("");
    ui->task_error_label->setVisible(false);

    connect(&taskThread,                 SIGNAL(OnTaskProgress(float)),     this,   SLOT(OnTaskProgress(float)));
    connect(&taskThread,                 SIGNAL(OnTaskSuccess()),           this,   SLOT(OnTaskSuccess()));
    connect(&taskThread,                 SIGNAL(OnTaskFail(int)),           this,   SLOT(OnTaskFail(int)));

    statusLabel = new TaskItemStatusLabel(this);
    ui->status_label->addWidget(statusLabel);

    showStatus();
}

TaskItem::~TaskItem()
{
    StopTask();
    if(statusLabel != nullptr){
        delete statusLabel;
        statusLabel = nullptr;
    }
    delete ui;
}


int TaskItem::SetParams(const YouTranscoderParams & _params)
{
    params = _params;
    return taskThread.SetParams(params);
}

int TaskItem::SetOutputDir(const QString & _output)
{
    outputDir = _output;
    return 0;
}

int TaskItem::SetFilenamePrefix(const QString & _filenamePrefix)
{
    filenamePrefix = _filenamePrefix;
    return 0;
}

int TaskItem::StartTask()
{
    QFileInfo fInput(taskThread.GetInputPath());

    QString filename = params.GetFilenamePrefix();

    filename = filename.simplified();

    filename = filename.replace("${origin_file_name}", fInput.baseName());
    filename = filename.replace("${output_video_codec}", params.GetVideoCodecId().GetDescName().c_str());
    filename = filename.replace("${output_audio_codec}", params.GetAudioCodecId().GetDescName().c_str());

    Eyer::EyerAVPixelFormat pixfmt = params.GetVideoPixelFormat();
    if(pixfmt == Eyer::EyerAVPixelFormat::EYER_KEEP_SAME){
        Eyer::EyerAVReader mediaInfo(taskThread.GetInputPath().toStdString());
        int ret = mediaInfo.Open();
        if(ret){
            taskThread.SetStatus(Eyer::EyerAVTranscoderStatus::FAIL);
            taskThread.SetErrorDesc("打开文件失败");
            showStatus();
            return -1;
        }
        int videoIndex = mediaInfo.GetVideoStreamIndex();
        if(videoIndex >= 0){
            Eyer::EyerAVStream videoStream = mediaInfo.GetStream(videoIndex);
            pixfmt = videoStream.GetPixelFormat();
        }
        mediaInfo.Close();
    }
    filename = filename.replace("${video_pixelfmt}", pixfmt.GetDescName().c_str());

    filename = filename.replace("/", "_");
    filename = filename.replace("H.265", "265");
    filename = filename.replace("H.264", "264");

    QString output = outputDir + "/" + filename + "." + params.GetOutputFileFmt().GetSuffix().c_str();

    QFileInfo fOutput(output);
    if(fOutput.exists()){
        taskThread.SetStatus(Eyer::EyerAVTranscoderStatus::FAIL);
        taskThread.SetErrorDesc("输出路径有重复文件");
        showStatus();
        return -1;
    }

    taskThread.SetOutput(output);
    taskThread.SetStatus(Eyer::EyerAVTranscoderStatus::ING);
    taskThread.start();
    return 0;
}

int TaskItem::StopTask()
{
    taskThread.Stop();
    return 0;
}

void TaskItem::OnTaskProgress(float progress)
{
    ui->task_progress_bar->setValue(progress * 100);
#ifndef WIN32
    ui->task_progress_label->setText( QString::number((int)(progress * 100)) + "%");
#else
    ui->task_progress_label->setText("");
#endif
    showStatus();
}

void TaskItem::OnTaskSuccess()
{
    ui->task_progress_bar->setValue(100);
#ifndef WIN32
    ui->task_progress_label->setText("100%");
#else
    ui->task_progress_label->setText("");
#endif
    showStatus();
    emit TaskItem_OnTaskSuccess();
}

void TaskItem::OnTaskFail(int code)
{
    showStatus();
    emit TaskItem_OnTaskFail(code);
}

int TaskItem::showStatus()
{
    Eyer::EyerAVTranscoderStatus status = taskThread.GetStatus();
    int width = ui->task_input_path->fontInfo().pixelSize() * 2.0;
    statusLabel->setMinimumSize(width, width);
    statusLabel->SetStatus(status);
    if(status == Eyer::EyerAVTranscoderStatus::FAIL){
        ui->task_error_label->setVisible(true);
        ui->task_error_label->setText(taskThread.GetErrorDesc());
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::darkRed);
        ui->task_error_label->setPalette(pe);
    }
    else {
        ui->task_error_label->setVisible(false);
    }
    return 0;
}

Eyer::EyerAVTranscoderStatus TaskItem::GetStatus()
{
    return taskThread.GetStatus();
}

int TaskItem::SetStatus(const Eyer::EyerAVTranscoderStatus & _status)
{
    return taskThread.SetStatus(_status);
}

void TaskItem::OnBtnRemove()
{
    emit TaskItem_OnRemove(this);
}
