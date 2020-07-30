#pragma once

#include <QtWidgets/qprogressbar.h>
#include <QtWidgets/qwidget>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>

#include <cstdio>
#include <array>


class ProgressBarWidget : public QWidget
{
    Q_OBJECT

    QProgressBar* bar = nullptr;
    QPushButton* stop = nullptr;
    std::array<QLabel*, 3> labels;
    std::atomic<bool> stopClicked = false;

    void initGui();


public slots:
    void OnSetCaption(const QString caption);
    void OnSetProgress(int newProgress);
    void OnSetText(int line, QString newText);

    void OnStopClicked();

signals:
    // Ensure that caption is set on the main thread.
    void setCaptionRequest(const QString caption);
    void setProgressRequest(int progress);
    void setTextRequest(int line, QString text);

    void hideRequest();
    void showRequest();

protected:
    virtual void closeEvent(QCloseEvent* event);

public:
    ProgressBarWidget() = delete;
    ProgressBarWidget(ProgressBarWidget&) = delete;
    ProgressBarWidget(QWidget* parent = nullptr) :
        QWidget(parent)

    {
        this->initGui();
        stopClicked.store(false);
    }

    bool StopClicked() { return stopClicked.load(); }
    bool StopClickedClear() { bool oldClicked = stopClicked.load(); stopClicked.store(false);  return oldClicked; }

    void SetCaption(const char* caption);
    void SetText(int line, const char* caption);
    void SetProgress(int progress);

    void Show() { emit showRequest(); }
    void Hide() { emit hideRequest(); stopClicked.store(true); }

};
