#ifndef YOUTRANSMAINWINDOW_HPP
#define YOUTRANSMAINWINDOW_HPP

#include <QMainWindow>
#include <QCloseEvent>

#include "TaskItem.hpp"

#include "YouTransConfig.hpp"

namespace Ui {
class YouTransMainWindow;
}

enum MainStatus
{
    ING, OTHER
};

class YouTransMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit YouTransMainWindow(QWidget *parent = nullptr);
    ~YouTransMainWindow();

    void ShowTranscoderParams();

    int UpdateSystemLabel();


protected:
    void closeEvent(QCloseEvent * event);

public slots:
    void SetInputPathClickListener();
    void SetOutputPathClickListener();
    void StartTranscodeConfigClickListener();
    void StartTranscodeClickListener();

    void OnConfigWindowsClose();

    void TaskItem_OnTaskSuccess();
    void TaskItem_OnTaskFail(int code);
    void TaskItem_OnRemove(TaskItem *);

private:

    void StartTranscodeClickListenerInternal();

    Ui::YouTransMainWindow *ui;

    YouTransConfig * configWindow = nullptr;

    YouTranscoderParams params;

    int SetStatusUI(MainStatus status);
};

#endif // YOUTRANSMAINWINDOW_HPP
