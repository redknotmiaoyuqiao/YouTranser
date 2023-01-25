#include "YouTransAboutWindow.hpp"
#include "ui_YouTransAboutWindow.h"

YouTransAboutWindow::YouTransAboutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YouTransAboutWindow)
{
    ui->setupUi(this);

    ui->about_text_browser->setReadOnly(true);
    // ui->about_text_browser->setText(EYER_HOST_SYSTEM_PROCESSOR);
}

YouTransAboutWindow::~YouTransAboutWindow()
{
    delete ui;
}
