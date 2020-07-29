#include "progressbar.h"
#include "progressbar_mgr.h"

#include <cstdio>

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qapplication.h>

#include <chrono>

using namespace std::chrono_literals;

void ProgressBarMgr::MainLoop()
{

    /* TODO: Set path to real application here */
    int argc = 1; 
    char* argv[] = {"this.exe"};
    
    this->windowShown = false;
    this->app.reset(new QApplication(argc, argv));
    this->widget.reset(new ProgressBarWidget(nullptr));
    this->app->setActiveWindow(this->widget.get());
    this->widget->show();
    this->windowShown = true;
    this->app->exec();
}
  

void ProgressBarMgr::MainLoopStart()
{
    if (mainLoopStarted) { return; }
    this->thread.reset(new std::thread(&ProgressBarMgr::MainLoop, this));
    
    // Wait for window creation, else NULL pointer reference
    while(!windowShown) { std::this_thread::yield(); }  
    mainLoopStarted = true;
}

void ProgressBarMgr::MainLoopStop()
{
    if (!mainLoopStarted) { return; }
    assert(this->app.get() != nullptr && "Null pointer for the APP");
    this->app->exit();
    this->thread->join();
}

ProgressBarMgr::~ProgressBarMgr()
{
    MainLoopStop();
}



