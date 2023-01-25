#ifndef TASKITEM_HPP
#define TASKITEM_HPP

#include <QWidget>
#include "TranscodeTaskThread.hpp"
#include "TaskItemStatusLabel.hpp"
#include "YouTranscoderParams.hpp"

namespace Ui {
class TaskItem;
}

class TaskItem : public QWidget
{
    Q_OBJECT

public:
    explicit TaskItem(QString inputPath, QWidget *parent = nullptr);
    ~TaskItem();

    int SetParams(const YouTranscoderParams & _params);
    int SetOutputDir(const QString & _output);
    int SetFilenamePrefix(const QString & _filenamePrefix);

    int StartTask();
    int StopTask();

    Eyer::EyerAVTranscoderStatus GetStatus();
    int SetStatus(const Eyer::EyerAVTranscoderStatus & _status);

    int showStatus();

public slots:
    void OnTaskProgress(float progress);
    void OnTaskSuccess();
    void OnTaskFail(int code);
    void OnBtnRemove();

signals:
    void TaskItem_OnTaskSuccess();
    void TaskItem_OnTaskFail(int code);

    void TaskItem_OnRemove(TaskItem * taskitem);

private:
    Ui::TaskItem *ui;

    TranscodeTaskThread taskThread;

    TaskItemStatusLabel * statusLabel = nullptr;

    YouTranscoderParams params;
    QString outputDir = "";
    QString filenamePrefix = "";
};

#endif // TASKITEM_HPP
