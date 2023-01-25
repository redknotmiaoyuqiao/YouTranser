#include "YPSessionCreateWindow.hpp"
#include "ui_YPSessionCreateWindow.h"

#include "YouPickerSession/YPSessionUtil.hpp"

#include <QDebug>

YPSessionCreateWindow::YPSessionCreateWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YPSessionCreateWindow)
{
    ui->setupUi(this);
    setWindowTitle("Session Create");

    // ui->edit_session_name->setFont();

    connect(ui->btn_create,       SIGNAL(clicked()),    this,   SLOT(BtnCreateClickListener()));
    connect(ui->btn_cancel,       SIGNAL(clicked()),    this,   SLOT(BtnCancelClickListener()));
}

YPSessionCreateWindow::~YPSessionCreateWindow()
{
    delete ui;
}

void YPSessionCreateWindow::BtnCreateClickListener()
{
    QString sessionName = ui->edit_session_name->text();

    if(sessionName.isEmpty()){
        ui->alert_label->setText("请输入 Session 名称");
        return;
    }

    Eyer::YPSessionUtil sessionUtil;
    sessionUtil.AddSession("sessionName");
    qDebug() << "Session Name: " << sessionName << Qt::endl;

    close();
}

void YPSessionCreateWindow::BtnCancelClickListener()
{
    close();
}

void YPSessionCreateWindow::closeEvent(QCloseEvent *)
{
    emit onClosed(0);
}
