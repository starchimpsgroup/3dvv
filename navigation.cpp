/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "navigation.h"
#include "ui_navigation.h"

Navigation::Navigation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Navigation)
{
    ui->setupUi(this);

    _play = false;

    QObject::connect(ui->positionSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
}

Navigation::~Navigation()
{
    delete ui;
}

void Navigation::sliderMoved(int value)
{
    emit positionChanged(value);
}

void Navigation::setSliderMaximum(int max)
{
    ui->positionSlider->setMaximum(max);
}

void Navigation::setSliderPosition(int pos)
{
    ui->positionSlider->setSliderPosition(pos);
}

void Navigation::on_playPause_clicked()
{
    if(_play)
    {
        _play = false;
        ui->playPause->setIcon(QIcon(":/navigation/play.png"));
    }
    else if(ui->positionSlider->sliderPosition() != ui->positionSlider->maximum())
    {
        _play = true;
        ui->playPause->setIcon(QIcon(":/navigation/pause.png"));
    }

    emit play(_play);
}

void Navigation::pause()
{
    if(_play)
    {
        _play = false;
        ui->playPause->setIcon(QIcon(":/navigation/play.png"));
    }
}

void Navigation::on_previous_clicked()
{
    emit step(-1);
}

void Navigation::on_next_clicked()
{
    emit step(1);
}
