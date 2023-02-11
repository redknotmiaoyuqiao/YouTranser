#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QMainWindow>
#include "MediaEyeApplication.h"

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutWindow(MediaEyeApplication & application, QWidget *parent = nullptr);
    ~AboutWindow();

public slots:
    void openUrl(QString url);

private:
    Ui::AboutWindow *ui;

    MediaEyeApplication app;
};

#endif // ABOUTWINDOW_H
