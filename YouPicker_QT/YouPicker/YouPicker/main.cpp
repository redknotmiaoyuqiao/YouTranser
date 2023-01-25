#include "MainWindow.h"

#include <QApplication>
#include <QStandardPaths>
#include <QFile>

#include "YouPickerLoading.hpp"
#include "YouPickerLogin.hpp"
#include "YPSessionListWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/you-picker.qss");
    if( qss.open(QFile::ReadOnly)) {
        qDebug() << "open success" << Qt::endl;
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else {
        qDebug() << "open failed" << Qt::endl;
    }

    QString HomeLocation = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    qDebug() << "HomeLocation=" << HomeLocation << Qt::endl;
    QString DocumentsLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    qDebug() << "DocumentsLocation=" << DocumentsLocation << Qt::endl;
    QString AppDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << "AppDataLocation=" << AppDataLocation << Qt::endl;
    QString AppLocalDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    qDebug() << "AppLocalDataLocation=" << AppLocalDataLocation << Qt::endl;


    Eyer::YouPickerAppConfig app;
    Eyer::YouPickerLoading loading(app);
    loading.show();

    // YPSessionListWindow sessionList;
    // sessionList.show();

    // Eyer::YouPickerLogin login(app);
    // login.show();

    return a.exec();
}
