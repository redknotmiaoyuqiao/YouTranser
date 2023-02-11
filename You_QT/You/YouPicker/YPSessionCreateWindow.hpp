#ifndef YPSESSIONCREATEWINDOW_H
#define YPSESSIONCREATEWINDOW_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class YPSessionCreateWindow;
}

class YPSessionCreateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit YPSessionCreateWindow(QWidget *parent = nullptr);
    ~YPSessionCreateWindow();

    void closeEvent(QCloseEvent *) override;

public slots:
    void BtnCreateClickListener();
    void BtnCancelClickListener();

signals:
    void onClosed(int type);

private:
    Ui::YPSessionCreateWindow *ui;
};

#endif // YPSESSIONCREATEWINDOW_H
