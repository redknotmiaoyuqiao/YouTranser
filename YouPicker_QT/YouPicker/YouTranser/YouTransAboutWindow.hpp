#ifndef YOUTRANSABOUTWINDOW_HPP
#define YOUTRANSABOUTWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class YouTransAboutWindow;
}

class YouTransAboutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit YouTransAboutWindow(QWidget *parent = nullptr);
    ~YouTransAboutWindow();

private:
    Ui::YouTransAboutWindow *ui;
};

#endif // YOUTRANSABOUTWINDOW_HPP
