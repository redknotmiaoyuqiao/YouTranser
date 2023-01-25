#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "MediaEyeApplication.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(const MediaEyeApplication & application, QWidget *parent = nullptr);
    ~LoginWindow();

    virtual int GotoMain() = 0;

private:
    Ui::LoginWindow *ui;
    QNetworkAccessManager * manage;

    MediaEyeApplication app;

public slots:
    void openUrl(QString url);
    void LoginClickListener();

    void OnNetworkProcessFinished(QNetworkReply *);
};

#endif // LOGINWINDOW_H
