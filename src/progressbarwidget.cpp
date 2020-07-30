#include "progressbarwidget.h"

#include <QtGui/qevent.h>
#include <QtWidgets/qlayout.h>

#include <QtCore/qsize.h>
#include <QtWidgets/qsizepolicy.h>

#include <cstdio>

void ProgressBarWidget::initGui()
{
    /*
     *  Create member widgets
     */

    this->stop = new QPushButton("Stop", this);
    this->bar = new QProgressBar(this);

    for (int n = 0; n < labels.size(); n++) {
        labels[n] = new QLabel("", this);
    }

    /*
     * Connect all signals
     */
    
    QObject::connect(this, &ProgressBarWidget::setCaptionRequest, this, &ProgressBarWidget::OnSetCaption);
    QObject::connect(this, &ProgressBarWidget::setProgressRequest, this, &ProgressBarWidget::OnSetProgress);
    QObject::connect(this, &ProgressBarWidget::setTextRequest, this, &ProgressBarWidget::OnSetText);
    QObject::connect(this, &ProgressBarWidget::showRequest, this, &ProgressBarWidget::show);
    QObject::connect(this, &ProgressBarWidget::hideRequest, this, &ProgressBarWidget::hide);

    //QObject::connect(stop, clicked)
    QObject::connect(stop, &QPushButton::clicked, this, &ProgressBarWidget::OnStopClicked);

    /*
     *  Instantiate widgets
     */

    QVBoxLayout* vblayout = new QVBoxLayout(this);
    const int width = 640;
    
    vblayout->addSpacerItem(new QSpacerItem(width, 5, QSizePolicy::Expanding, QSizePolicy::Expanding));

    for (int n = 0; n < labels.size(); n++) {
        vblayout->addWidget(labels[n]);
    }
    vblayout->addWidget(this->bar);

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addSpacerItem(new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hbox->addWidget(this->stop);
    hbox->addSpacerItem(new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    vblayout->addLayout(hbox);
    vblayout->addSpacerItem(new QSpacerItem(width, 5, QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->setLayout(vblayout);
}

void ProgressBarWidget::SetCaption(const char * caption)
{
    QString newCaption = (caption != nullptr)? QString(caption) : QString("Got NULL Pointer");
    emit setCaptionRequest(newCaption);
}


void ProgressBarWidget::SetText(int line, const char* text)
{
    QString newText = (text != nullptr)? QString(text) : QString("Got NULL Pointer");
    emit setTextRequest(line, newText);

}

void ProgressBarWidget::SetProgress(int progress)
{
    emit setProgressRequest(progress);
}

void ProgressBarWidget::OnSetCaption(const QString newCaption)
{
    if (this->isHidden()) { this->show(); };
    
    this->setWindowTitle(newCaption);
}


void ProgressBarWidget::OnSetText(int line, QString text)
{
    if (this->isHidden()) { this->show(); };
    
    int n = line % labels.size();
    labels[n]->setText(text);
} 

void ProgressBarWidget::OnSetProgress(int progress)
{
    if (this->isHidden()) { this->show(); };

    progress = progress % bar->maximum();
    bar->setValue(progress);
}

void ProgressBarWidget::OnStopClicked()
{
    stopClicked.store(true);
}


/*
 *   Overridden events
 */

void ProgressBarWidget::closeEvent(QCloseEvent* event)
{
    // A better closing strategy with blocking
    //event->ignore();
    // this->stopClicked = true;
}
