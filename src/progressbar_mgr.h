#pragma once

#include "progressbarwidget.h"
#include <QtWidgets/qapplication.h>

#include <memory>
#include <thread>

class ProgressBarMgr
{
private:
    std::unique_ptr<ProgressBarWidget> widget;
    std::unique_ptr<std::thread> thread;
    std::unique_ptr<QApplication> app;
    bool  mainLoopStarted;
    bool windowShown;

    void MainLoop();
    void MainLoopStart();
    void MainLoopStop();

public:
    ProgressBarMgr() : widget(nullptr), thread(nullptr), app(nullptr), mainLoopStarted(false), windowShown(false) {};
    ~ProgressBarMgr();

    void SetCaption(const char* caption) {
        MainLoopStart();
        this->widget->SetCaption(caption);
    }

    void SetProgress(int progress)
    {
        MainLoopStart();
        this->widget->SetProgress(progress);
    }

    void SetText(int line, const char* caption)
    {
        MainLoopStart();
        this->widget->SetText(line, caption);
    }

    bool StopClicked()
    {
        MainLoopStart();
        return this->widget->StopClicked();
    }

    bool StopClickedClear()
    {
        MainLoopStart();
        return this->widget->StopClickedClear();
    }

};
