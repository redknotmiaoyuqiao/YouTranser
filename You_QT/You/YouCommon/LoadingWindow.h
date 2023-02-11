#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QNetworkReply>
#include "MediaEyeApplication.h"
#include "LoadingTimerThread.h"

namespace Ui {
class LoadingWindow;
}

class LoadingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingWindow(const MediaEyeApplication & application, QWidget *parent = nullptr);
    virtual ~LoadingWindow();

    virtual int GotoLogin() = 0;
    virtual int GotoMain() = 0;

private:
    Ui::LoadingWindow *ui;

    MediaEyeApplication app;

    LoadingTimerThread * timerThread = NULL;

    int MyClose();

public slots:
    void timeoutSig();
    void OnNetworkProcessFinished(QNetworkReply *);
};

#endif // LOADINGWINDOW_H
