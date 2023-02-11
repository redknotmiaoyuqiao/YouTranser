#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>

LoginWindow::LoginWindow(const MediaEyeApplication & _application, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    app = _application;

    ui->setupUi(this);
    setWindowTitle(app.GetAppName());

    ui->error_label->setText("");

    ui->password_line_edit->setEchoMode(QLineEdit::Password);
    // QFont font("宋体", 20, QFont::Thin);
    // ui->login_label->setFont(font);
    // ui->login_label->setText(" ");

    ui->regiest_label->setText(("<a style='color:blue;' href='https://www.zzsin.com/register.html'>注册账号</a>"));
    ui->forget_pw_label->setText(("<a style='color:blue;' href='https://www.zzsin.com/find_pw.html'>忘记密码</a>"));
    connect(ui->regiest_label,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
    connect(ui->forget_pw_label,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
    connect(ui->login_btn,       SIGNAL(clicked()),    this,   SLOT(LoginClickListener()));

    manage = new QNetworkAccessManager(this);       //分配空间
    connect(manage,SIGNAL(finished(QNetworkReply*)),this,SLOT(OnNetworkProcessFinished(QNetworkReply*)));

    QImage img;
    img.load(app.GetLogoPath());
    img = img.scaledToWidth(100, Qt::SmoothTransformation);
    ui->logo_label->setPixmap(QPixmap::fromImage(img));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void LoginWindow::LoginClickListener()
{
    QString email = ui->email_line_edit->text();
    if(email == ""){
        ui->error_label->setText("请输入邮箱");
        // QMessageBox::information(NULL, "请输入邮箱", "请输入邮箱");
        return;
    }
    QString password = ui->password_line_edit->text();
    if(password == ""){
        ui->error_label->setText("请输入密码");
        // QMessageBox::information(NULL, "请输入密码", "请输入密码");
        return;
    }
    // 本地缓存设置保存EMAIL，到了网络回调，如果登录失败就再去掉
    QSettings setting(app.GetCompanyName(), app.GetAppId());
    setting.setValue(app.GetKEY_EMAIL(), email);

    QNetworkRequest req;
    req.setUrl(QUrl(app.GetLoginURL()));

    QByteArray post_data;

    post_data.append("email=" + QUrl::toPercentEncoding(email) + "&");
    post_data.append("password=" +  QUrl::toPercentEncoding(password) + "&");
#if defined(Q_OS_WIN)
    post_data.append("platform=windows&");
#elif defined(Q_OS_OSX)
    post_data.append("platform=macosx&");
#elif defined(Q_OS_LINUX)
    post_data.append("platform=linux&");
#else
    post_data.append("platform=other&");
#endif
    QString params = QString("app_name=") + app.GetAppId() + "&" + QString("version=") + app.GetVersion() + "";
    post_data.append(params.toUtf8());
    // post_data.append("app_name=" + application.GetAppId() + "&");
    // post_data.append("version=" + application.GetVersion() + "");

    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

    manage->post(req, post_data);
}

void LoginWindow::OnNetworkProcessFinished(QNetworkReply * reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid()){
        qDebug() << "status code=" << statusCode.toInt();
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid()){
        qDebug() << "reason=" << reason.toString();
    }

    QSettings setting(app.GetCompanyName(), app.GetAppId());
    QNetworkReply::NetworkError err = reply->error();

    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
        ui->error_label->setText("网络错误");
        // QMessageBox::information(NULL, "网络错误", "网络错误");
        setting.setValue(app.GetKEY_EMAIL(), "");
    } else {
        QByteArray res = reply->readAll();

        qDebug() << QString(res) << Qt::endl;

        QJsonObject jsonObj = QJsonDocument::fromJson(res).object();
        int code = jsonObj.find("code")->toInt();

        qDebug() << jsonObj << Qt::endl;

        qDebug() << "code:" << code << Qt::endl;
        if(code == 200){
            QJsonObject model = jsonObj.find("model")->toObject();
            QString token = model.find("token")->toString();

            QSettings setting(app.GetCompanyName(), app.GetAppId());
            setting.setValue(app.GetKEY_TOKEN(), token);
            long long nowTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
            setting.setValue(app.GetKEY_TOKEN_UPDATE_TIME(), nowTime);

            GotoMain();

            close();
        }
        else{
            setting.setValue(app.GetKEY_EMAIL(), "");
            ui->error_label->setText("用户名或密码错误");
            // QMessageBox::information(NULL, "用户名或密码错误", "用户名或密码错误");
        }
    }
}

