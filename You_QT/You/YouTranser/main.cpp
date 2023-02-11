#include <QApplication>
#include <QStandardPaths>
#include <QFile>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QApplication>

#ifdef WIN32
// #include <QDesktopWidget>
#endif

#include <MainWindow.h>

#include "YouTransLoading.hpp"
#include "YouTransMainWindow.hpp"
#include "YouTransAppConfig.hpp"
#include "YouTransAboutWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList list = QStyleFactory::keys();
    foreach(const QString &str,list) {
        qDebug() << str << Qt::endl;
    }

    // QStyle* style = QStyleFactory::create("Fusion");
    // a.setStyle(style);

    /*
    int font_Id = QFontDatabase::addApplicationFont(":/font/SmileySans-Oblique.otf");
    QStringList font_list = QFontDatabase::applicationFontFamilies(font_Id);
    qDebug()<<font_Id;
    qDebug()<<font_list;
    if(!font_list.isEmpty())
    {
        QFont f;
        f.setFamily(font_list[0]);
        a.setFont(f);
    }
    */

    // QFont f("微软雅黑");
    // a.setFont(f);

    /*
// #ifndef WIN32
    QFile qss(":/you-trans.qss");
    if( qss.open(QFile::ReadOnly)) {
        qDebug() << "open success" << Qt::endl;
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else {
        qDebug() << "open failed" << Qt::endl;
    }
// #endif
    */

    Eyer::YouTransAppConfig app;
    Eyer::YouTransLoading loading(app);
#ifdef WIN32
    // QDesktopWidget *desktop = QApplication::desktop();
    // loading.move((desktop->width() - loading.width())/ 2, (desktop->height() - loading.height()) /2);
#endif
    loading.show();

    // YouTransMainWindow mainWin;
    // mainWin.show();

    // YouTransAboutWindow about;
    // about.show();

    return a.exec();
}
