#include "LoadingWindow.h"
#include "ui_LoadingWindow.h"
#include "LoadingWindow.h"
#include "LoginWindow.h"
#include <QSettings>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

LoadingWindow::LoadingWindow(const MediaEyeApplication & application, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadingWindow)
{
    app = application;

    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

    timerThread = new LoadingTimerThread();
    connect(timerThread, SIGNAL(OnTimeout()), this, SLOT(timeoutSig()));
    timerThread->start();

    // QTimer *timer = new QTimer(this);
    // connect(timer, SIGNAL(timeout()), this, SLOT(timeoutSig()));
    // timer.setSingleShot(true);
    // timer->start(2 * 1000);

    QFont titleFont;
    titleFont.setPointSize(40);
    titleFont.setBold(true);
    ui->title_label->setFont(titleFont);

    ui->title_label->setText(app.GetAppName());


    QFont versionFont;
    versionFont.setPointSize(12);
    ui->version_label->setFont(versionFont);
    ui->version_label->setText(app.GetVersion());

    QFont subTitleFont;
    subTitleFont.setPointSize(12);
    ui->sub_title_label->setFont(subTitleFont);
    ui->sub_title_label->setText(app.GetCompanyName());

    QImage img;
    // qDebug() << app.GetLogoPath() << Qt::endl;
    img.load(app.GetLogoPath());
    int width = ui->title_label->fontInfo().pixelSize() * 1.5;
    img = img.scaledToWidth(width * 1.5, Qt::SmoothTransformation);
    ui->logo_img->setPixmap(QPixmap::fromImage(img));


    resize(width * 7, width * 3);

    // resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

LoadingWindow::~LoadingWindow()
{
    if(timerThread != nullptr){
        timerThread->wait();
        delete timerThread;
        timerThread = nullptr;
    }
    delete ui;
}

void LoadingWindow::timeoutSig()
{
    QSettings setting(app.GetCompanyName(), app.GetAppId());
    QString token = setting.value(app.GetKEY_TOKEN(), "").toString();

    qDebug() << token << Qt::endl;

    if(token == ""){
        GotoLogin();
        MyClose();
        return;
    }

    QNetworkAccessManager * manage = new QNetworkAccessManager(this);
    connect(manage,SIGNAL(finished(QNetworkReply*)),this,SLOT(OnNetworkProcessFinished(QNetworkReply*)));

    QNetworkRequest req;
    req.setUrl(QUrl(app.GetLoginCheckURL()));

    QByteArray post_data;

    post_data.append("token=" + QUrl::toPercentEncoding(token) + "&");
#if defined(Q_OS_WIN32)
    post_data.append("platform=windows&");
#else
    post_data.append("platform=macosx&");
#endif
    // post_data.append(QString("app_name=") + app.GetAppId() + "&");
    // post_data.append(QString("version=") + app.GetVersion() + "");
    QString params = QString("app_name=") + app.GetAppId() + "&" + QString("version=") + app.GetVersion() + "";
    post_data.append(params.toUtf8());

    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

    manage->post(req, post_data);
}

void LoadingWindow::OnNetworkProcessFinished(QNetworkReply * reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid()){
        qDebug() << "status code=" << statusCode.toInt();
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid()){
        qDebug() << "reason=" << reason.toString();
    }


    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();

        long long nowTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        QSettings setting(app.GetCompanyName(), app.GetAppId());
        long long saveTime = (long long)setting.value(app.GetKEY_TOKEN_UPDATE_TIME(), 0).toDouble();

        if(nowTime - saveTime <= 60 * 60 * 24 * 7){
            GotoMain();
            MyClose();
        }
        else{
            GotoLogin();
            MyClose();
        }
    }
    else {
        QByteArray res = reply->readAll();

        qDebug() << res << Qt::endl;

        QJsonObject jsonObj = QJsonDocument::fromJson(res).object();
        int code = jsonObj.find("code")->toInt();

        if(code == 200){
            long long nowTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
            QSettings setting(app.GetCompanyName(), app.GetAppId());
            setting.setValue(app.GetKEY_TOKEN_UPDATE_TIME(), nowTime);

            GotoMain();
            // GotoLogin();
            MyClose();
        }
        else if(code == 501){
            QSettings setting(app.GetCompanyName(), app.GetAppId());
            setting.setValue(app.GetKEY_TOKEN(), "");

            GotoLogin();
            MyClose();
        }
        else if(code == 502){
            QSettings setting(app.GetCompanyName(), app.GetAppId());
            setting.setValue(app.GetKEY_TOKEN(), "");

            GotoLogin();
            MyClose();
        }
        else{
            QSettings setting(app.GetCompanyName(), app.GetAppId());
            setting.setValue(app.GetKEY_TOKEN(), "");

            GotoLogin();
            MyClose();
        }
    }
}

int LoadingWindow::MyClose()
{
    timerThread->wait();
    // qDebug() << "LoadingWindow::MyClose()" << Qt::endl;
    // disconnect(&timer, SIGNAL(timeout()), this, SLOT(timeoutSig()));
    // timer.stop();
    this->close();
    // exit(0);
    return 0;
}
