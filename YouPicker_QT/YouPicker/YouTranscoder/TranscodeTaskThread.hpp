#ifndef TRANSCODETASKTHREAD_HPP
#define TRANSCODETASKTHREAD_HPP

#include <mutex>

#include <QThread>

#include "EyerAVTranscoder/EyerAVTranscoderHeader.hpp"

class TranscodeTaskThread : public QThread, public Eyer::EyerAVTranscoderListener, public Eyer::EyerAVTranscoderInterrupt
{
    Q_OBJECT
public:
    TranscodeTaskThread(const QString & _input);
    ~TranscodeTaskThread();

    int Stop();

    QString GetInputPath() const;

    int SetParams(const Eyer::EyerAVTranscoderParams & _params);
    int SetOutput(const QString & _output);

    Eyer::EyerAVTranscoderStatus GetStatus();
    int SetStatus(const Eyer::EyerAVTranscoderStatus & _status);

    QString GetErrorDesc();
    int SetErrorDesc(const QString & errorDesc);

    void run() override;

    virtual int OnProgress(float progress) override;
    virtual int OnFail(Eyer::EyerAVTranscoderError & code) override;
    virtual int OnSuccess() override;

    virtual bool interrupt() override;

signals:
    void OnTaskProgress(float progress);
    void OnTaskFail(int code);
    void OnTaskSuccess();

private:
    QString input;
    QString output;

    Eyer::EyerAVTranscoder * transcoder = nullptr;

    Eyer::EyerAVTranscoderParams params;

    std::mutex interruptFlagMut;
    bool interruptFlag = false;
};

#endif // TRANSCODETASKTHREAD_HPP
