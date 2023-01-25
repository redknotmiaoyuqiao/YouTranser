#include "TaskItemStatusLabel.hpp"

#include <QPainter>
#include <QDebug>
#include "EyerCore/EyerCore.hpp"

TaskItemStatusLabel::TaskItemStatusLabel(QWidget * parent)
    : QWidget(parent)
{
    connect(&mTime, &QTimer::timeout, this, &TaskItemStatusLabel::MyTimerEvent);
}

TaskItemStatusLabel::~TaskItemStatusLabel()
{

}

void TaskItemStatusLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect geo = this->geometry();

    int width = geo.width();
    int height = geo.height();

    painter.eraseRect(0, 0, width, height);

    if(status == Eyer::EyerAVTranscoderStatus::ING){
        drawIng(painter, width, height);
    }
    else if(status == Eyer::EyerAVTranscoderStatus::PREPARE){
        drawWait(painter, width, height);
    }
    else if(status == Eyer::EyerAVTranscoderStatus::FAIL){
        drawAlert(painter, width, height);
    }
    else if(status == Eyer::EyerAVTranscoderStatus::SUCC){
        drawSucc(painter, width, height);
    }
}

int TaskItemStatusLabel::SetStatus(Eyer::EyerAVTranscoderStatus _status)
{
    status = _status;

    if(status == Eyer::EyerAVTranscoderStatus::ING){
        mTime.start();
    }
    else {
        mTime.stop();
    }
    update();
    return 0;
}

void TaskItemStatusLabel::MyTimerEvent ()
{
    update();
}

int TaskItemStatusLabel::drawAlert   (QPainter &painter, int width, int height)
{
    painter.setPen(QPen(Qt::blue, 1, Qt::NoPen));
    painter.setBrush(QColor(150, 0, 0));

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(0, 0, width, height);


    painter.setBrush(QColor(235, 235, 235));
    // painter.setBrush(QColor(0, 0, 0));
    float ellipseR = height * 0.035;
    painter.drawEllipse(QPointF(width / 2, height * 0.75), ellipseR * 2, ellipseR * 2);
    painter.drawEllipse(QPointF(width / 2, height * 0.25), ellipseR * 2, ellipseR * 2);
    painter.drawEllipse(QPointF(width / 2, height * 0.55), ellipseR * 2 * 0.8, ellipseR * 2 * 0.8);

    painter.setBrush(QColor(235, 235, 235));
    static const QPointF points[4] = {
            QPointF(width / 2 - ellipseR * 2, height * 0.25),
            QPointF(width / 2 + ellipseR * 2, height * 0.25),

            QPointF(width / 2 + ellipseR * 2 * 0.8, height * 0.55),
            QPointF(width / 2 - ellipseR * 2 * 0.8, height * 0.55),
    };
    painter.drawPolygon(points, 4);

    return 0;
}

int TaskItemStatusLabel::drawIng     (QPainter & painter, int width, int height)
{
    painter.setPen(QPen(Qt::blue, 1, Qt::NoPen));
    painter.setBrush(QColor(20, 0, 150));

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(0, 0, width, height);

    painter.setBrush(QColor(235, 235, 235));

    painter.translate(width / 2, height / 2);
    painter.rotate(time);
    float ellipseR = height * 0.05;

    painter.drawEllipse(QPointF(0.0, height / 4.0), ellipseR * 2, ellipseR * 2);
    painter.drawEllipse(QPointF(0.0, -height / 4.0), ellipseR * 2, ellipseR * 2);
    painter.drawEllipse(QPointF(width / 4.0, 0.0), ellipseR * 2, ellipseR * 2);
    painter.drawEllipse(QPointF(- width / 4.0, 0.0), ellipseR * 2, ellipseR * 2);

    // EyerLog("RRR: %f\n", time);
    time += 0.01;
    if(time >= 360.0){
        time = 0.0;
    }
    return 0;
}

int TaskItemStatusLabel::drawSucc    (QPainter & painter, int width, int height)
{
    painter.setPen(QPen(Qt::blue, 1, Qt::NoPen));
    painter.setBrush(QColor(0, 150, 10));

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(0, 0, width, height);

    painter.setBrush(QColor(235, 235, 235));
    float k = 0.6;
    static const QPointF points[6] = {
            QPointF(0               * width * k + width * (1.0 - k) * 0.5,   50.45 / 100.0 * height * k + height * (1.0 - k) * 0.5),
            QPointF(10.7    / 100.0 * width * k + width * (1.0 - k) * 0.5,   41.8  / 100.0 * height * k + height * (1.0 - k) * 0.5),
            QPointF(35.05   / 100.0 * width * k + width * (1.0 - k) * 0.5,   60.85 / 100.0 * height * k + height * (1.0 - k) * 0.5),
            QPointF(97.45   / 100.0 * width * k + width * (1.0 - k) * 0.5,   6.85  / 100.0 * height * k + height * (1.0 - k) * 0.5),
            QPointF(100.0   / 100.0 * width * k + width * (1.0 - k) * 0.5,   12.8  / 100.0 * height * k + height * (1.0 - k) * 0.5),
            QPointF(41.95   / 100.0 * width * k + width * (1.0 - k) * 0.5,   93.15 / 100.0 * height * k + height * (1.0 - k) * 0.5),
    };
    painter.drawPolygon(points, 6);

    return 0;
}

int TaskItemStatusLabel::drawWait    (QPainter & painter, int width, int height)
{
    painter.setPen(QPen(Qt::blue, 1, Qt::NoPen));
    painter.setBrush(QColor(0, 143, 150));

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(0, 0, width, height);

    painter.setBrush(QColor(235, 235, 235));
    int smallEllipseC = height / 5;
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawEllipse(width / 2 - smallEllipseC / 2, height / 2 - smallEllipseC / 2, smallEllipseC, smallEllipseC);
    painter.drawEllipse(width / 2 - smallEllipseC / 2 - smallEllipseC * 1.5, height / 2 - smallEllipseC / 2, smallEllipseC, smallEllipseC);
    painter.drawEllipse(width / 2 - smallEllipseC / 2 + smallEllipseC * 1.5, height / 2 - smallEllipseC / 2, smallEllipseC, smallEllipseC);

    return 0;
}
