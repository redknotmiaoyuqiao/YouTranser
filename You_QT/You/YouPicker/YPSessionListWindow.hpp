#ifndef YPSESSIONLISTWINDOW_H
#define YPSESSIONLISTWINDOW_H

#include <QMainWindow>

#include "YouCommon/EyerQFlowLayout.h"

namespace Ui {
class YPSessionListWindow;
}

class YPSessionListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit YPSessionListWindow(QWidget *parent = nullptr);
    ~YPSessionListWindow();

    int listAllSession();

public slots:
    void CreateSessionClickListener();
    void onCreateSessionClosed(int type);

private:
    Ui::YPSessionListWindow *ui;

    EyerQFlowLayout * flowLayout = nullptr;
};

#endif // YPSESSIONLISTWINDOW_H
