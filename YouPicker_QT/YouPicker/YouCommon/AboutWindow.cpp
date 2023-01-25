#include "AboutWindow.h"
#include "ui_AboutWindow.h"
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

AboutWindow::AboutWindow(MediaEyeApplication & application, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    app = application;

    setWindowTitle(application.GetAppName() + " About");

    QFont titleFont;
    titleFont.setPointSize(25);
    titleFont.setFamily("黑体");
    titleFont.setBold(true);
    ui->title_label->setFont(titleFont);
    ui->title_label->setText(app.GetAppName() + " " + app.GetVersion());

    QFont subTitleFont;
    subTitleFont.setFamily("黑体");
    subTitleFont.setPointSize(15);
    ui->sub_title_label->setFont(subTitleFont);
    ui->sub_title_label->setText(app.GetCompanyName());

    QImage img;
    qDebug() << app.GetLogoPath() << Qt::endl;
    img.load(app.GetLogoPath());
    img = img.scaledToWidth(100, Qt::SmoothTransformation);
    ui->logo_img->setPixmap(QPixmap::fromImage(img));

    ui->website->setText(("<a style='color:blue;' href='https://www.zzsin.com'>www.zzsin.com</a>"));
    connect(ui->website,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}

