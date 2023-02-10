#ifndef YOUTRANSCONFIG_HPP
#define YOUTRANSCONFIG_HPP

#include <QMainWindow>

#include "YouTranscoderParams.hpp"

#include "EyerAVTranscoder/EyerAVTranscoderHeader.hpp"

namespace Ui {
class YouTransConfig;
}

class YouTransConfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit YouTransConfig(const YouTranscoderParams & inputParams, QWidget *parent = nullptr);
    ~YouTransConfig();

protected:
     void closeEvent(QCloseEvent *event);

public slots:
    void onCurrentIndexChanged(int index);

    void onAVFileFmtCurrentIndexChanged(int index);
    void onVideoCodecCurrentIndexChanged(int index);
    void onAudioCodecCurrentIndexChanged(int index);
    void onChannellayoutCurrentIndexChanged(int index);
    void onCRFValueChanged(int value);

    void OkayClickListener();
    void CancelClickListener();

    void SetCurrentData();


    YouTranscoderParams GetTranscodeParams();
signals:
    void OnConfigWindowsClose();

private:
    Ui::YouTransConfig *ui;

    YouTranscoderParams params;
};

#endif // YOUTRANSCONFIG_HPP
