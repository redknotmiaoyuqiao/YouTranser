#include "YPSessionListWindow.hpp"
#include "ui_YPSessionListWindow.h"
#include "YPSessionCreateWindow.hpp"

#include "YouPickerSession/YPSessionUtil.hpp"

#include "YouCommon/EyerQFlowLayout.h"

#include <QDebug>

YPSessionListWindow::YPSessionListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YPSessionListWindow)
{
    ui->setupUi(this);
    setWindowTitle("Session List");

    connect(ui->btn_create_session,       SIGNAL(clicked()),    this,   SLOT(CreateSessionClickListener()));

    flowLayout = new EyerQFlowLayout();
    ui->scroll_area_layout->addLayout(flowLayout);
    listAllSession();
}

YPSessionListWindow::~YPSessionListWindow()
{
    delete ui;
}

int YPSessionListWindow::listAllSession()
{
    Eyer::YPSessionUtil sessionUtil;
    std::vector<Eyer::YPSession> sessionList = sessionUtil.GetSessiones();

    flowLayout->removeAllItem();
    qDebug() << "sessionList: " << sessionList.size() << Qt::endl;
    for(int i=0;i<sessionList.size();i++){
        Eyer::YPSession session = sessionList[i];
        qDebug() << "Session Name: " << session.sessionName.c_str() << Qt::endl;

        flowLayout->addWidget(new QPushButton(tr(session.sessionName.c_str())));
    }

    return 0;
}

void YPSessionListWindow::CreateSessionClickListener()
{
    YPSessionCreateWindow * createSession = new YPSessionCreateWindow(this);
    connect(createSession, SIGNAL(onClosed(int)), this, SLOT(onCreateSessionClosed(int)));
    createSession->setWindowModality(Qt::ApplicationModal);
    createSession->show();
}

void YPSessionListWindow::onCreateSessionClosed(int type)
{
    qDebug() << "onCreateSessionClosed: " << type << Qt::endl;
    listAllSession();
}
