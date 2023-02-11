#include "TranscodeTaskThread.hpp"

#include <QDebug>

#include <QFileInfo>

TranscodeTaskThread::TranscodeTaskThread(const QString & _input)
{
    input = _input;
    QFileInfo fInput(input);
    transcoder = new Eyer::EyerAVTranscoder(input.toStdString());
}

TranscodeTaskThread::~TranscodeTaskThread()
{
    if(transcoder != nullptr){
        delete transcoder;
        transcoder = nullptr;
    }
}

int TranscodeTaskThread::Stop()
{
    {
        std::lock_guard<std::mutex> lock(interruptFlagMut);
        interruptFlag = true;
    }
    wait();
    return 0;
}

int TranscodeTaskThread::SetParams(const Eyer::EyerAVTranscoderParams & _params)
{
    params = _params;
    return 0;
}

int TranscodeTaskThread::SetOutput(const QString & _output)
{
    output = _output;
    return 0;
}

void TranscodeTaskThread::run()
{
    EyerLog("TranscodeTaskThread Start\n");
    transcoder->SetOutputPath(output.toStdString());
    transcoder->SetParams(params);
    transcoder->SetListener(this);
    transcoder->Transcode(this);
    EyerLog("TranscodeTaskThread End\n");
}

bool TranscodeTaskThread::interrupt()
{
    std::lock_guard<std::mutex> lock(interruptFlagMut);
    return interruptFlag;
}

int TranscodeTaskThread::OnProgress(float progress)
{
    emit OnTaskProgress(progress);
    return 0;
}

int TranscodeTaskThread::OnFail(Eyer::EyerAVTranscoderError & code)
{
    EyerLog("OnFail: %s\n", code.GetDesc().c_str());
    emit OnTaskFail(code.GetCode());
    return 0;
}

int TranscodeTaskThread::OnSuccess()
{
    EyerLog("OnSuccess\n");
    emit OnTaskSuccess();
    return 0;
}

Eyer::EyerAVTranscoderStatus TranscodeTaskThread::GetStatus(){
    return transcoder->GetStatus();
}

int TranscodeTaskThread::SetStatus(const Eyer::EyerAVTranscoderStatus & _status)
{
    return transcoder->SetStatus(_status);
}

int TranscodeTaskThread::SetErrorDesc(const QString & errorDesc)
{
    return transcoder->SetErrorDesc(errorDesc.toStdString().c_str());
}

QString TranscodeTaskThread::GetErrorDesc()
{
    return transcoder->GetErrorDesc().c_str();
}

QString TranscodeTaskThread::GetInputPath() const
{
    return input;
}
