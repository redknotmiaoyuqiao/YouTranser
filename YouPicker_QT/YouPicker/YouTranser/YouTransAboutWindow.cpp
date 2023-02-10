#include "YouTransAboutWindow.hpp"
#include "ui_YouTransAboutWindow.h"

#include "YouTransAppConfig.hpp"
#include "YouTransConfig.hpp"

YouTransAboutWindow::YouTransAboutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YouTransAboutWindow)
{
    ui->setupUi(this);

    Eyer::YouTransAppConfig app;
    setWindowTitle(app.GetAppName());
    setWindowIcon(QIcon(app.GetLogoPath()));

    ui->about_text_browser->setReadOnly(true);
    ui->about_text_browser->setSource(QUrl("qrc:/docs/thirdPart_LICENSE.md"));

    QImage img;
    img.load(app.GetLogoPath());
    int width = ui->about_version_label->fontInfo().pixelSize() * 10;
    img = img.scaledToWidth(width, Qt::SmoothTransformation);
    ui->about_logo_label->setPixmap(QPixmap::fromImage(img));

    ui->about_version_label->setText("<h3>" + app.GetAppName() + "</h3>" + app.GetVersion() + "<p>" + "https://www.zzsin.com" + "</p>");
}

YouTransAboutWindow::~YouTransAboutWindow()
{
    delete ui;
}
