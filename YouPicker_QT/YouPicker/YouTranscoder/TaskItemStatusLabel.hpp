#ifndef TASKITEMSTATUSLABEL_HPP
#define TASKITEMSTATUSLABEL_HPP

#include <QWidget>
#include <QTimer>
#include "EyerAVTranscoder/EyerAVTranscoderStatus.hpp"

namespace Ui {
    class TaskItemStatusLabel;
}

class TaskItemStatusLabel : public QWidget
{
    Q_OBJECT
public:
    explicit TaskItemStatusLabel(QWidget *parent = nullptr);
    ~TaskItemStatusLabel();

    void paintEvent(QPaintEvent *event) override;

    int SetStatus(Eyer::EyerAVTranscoderStatus _status);

    void MyTimerEvent ();

private:
    int drawAlert   (QPainter & painter, int width, int height);
    int drawIng     (QPainter & painter, int width, int height);
    int drawSucc    (QPainter & painter, int width, int height);
    int drawWait    (QPainter & painter, int width, int height);

    Eyer::EyerAVTranscoderStatus status = status.PREPARE;

    float time = 0;

    QTimer mTime;
};

#endif // TASKITEMSTATUSLABEL_HPP
