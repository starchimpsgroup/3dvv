/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(rejected()), this, SLOT(abort()));
    _backgroundColorDialog = new QColorDialog(this);
    _highlightColorDialog  = new QColorDialog(this);
}

Preferences::~Preferences()
{
    delete _backgroundColorDialog;
    delete _highlightColorDialog;
    delete ui;
}

void Preferences::on_backgroundColorButton_clicked()
{
    _backgroundColorDialog->exec();
    QColor selectedColor  = _backgroundColorDialog->selectedColor();
    setBackgroundColorButtonColor(selectedColor, false);

    emit changeBackgroundColor(selectedColor);
}

void Preferences::on_ids_stateChanged(int state)
{
    emit showObjectIds(state);
}

void Preferences::on_coordinates_stateChanged(int state)
{
    emit showCoordinates(state);
}

void Preferences::on_vectors_stateChanged(int state)
{
    emit showVectors(state);
}

void Preferences::setBackgroundColorButtonColor(GLColor color, bool save)
{
    if(save)
        _backgroundColor = color;

    ui->backgroundColorButton->setStyleSheet("background-color: rgb(" + QString::number(color.redDez())   + ", "
                                                                      + QString::number(color.greenDez()) + ", "
                                                                      + QString::number(color.blueDez())  + ");");
}

void Preferences::setShowObjectIds(int state)
{
    _showObjectIds = state;
    ui->ids->setCheckState((Qt::CheckState)state);
}

void Preferences::setShowCoordinates(int state)
{
    _showCoordinates = state;
    ui->coordinates->setCheckState((Qt::CheckState)state);
}

void Preferences::setShowVectors(int state)
{
    _showVectors = state;
    ui->vectors->setCheckState((Qt::CheckState)state);
}

void Preferences::on_highlightColorButton_clicked()
{
    _highlightColorDialog->exec();
    QColor selectedColor  = _highlightColorDialog->selectedColor();
    setHighlightColorButtonColor(selectedColor, false);

    emit changeHighlightColor(selectedColor);
}

void Preferences::on_highlight_stateChanged(int state)
{
    emit showHighlightObjects(state);
}

void Preferences::on_highlightTimeSpinBox_valueChanged(int i)
{
    emit changeHighlightTime(i);
}

void Preferences::on_highlightRateSpinBox_valueChanged(int i)
{
    emit changeHighlightRate(i);
}

void Preferences::setHighlightColorButtonColor(GLColor color, bool save)
{
    if(save)
        _highlightColor = color;

    ui->highlightColorButton->setStyleSheet("background-color: rgb(" + QString::number(color.redDez())   + ", "
                                                                     + QString::number(color.greenDez()) + ", "
                                                                     + QString::number(color.blueDez())  + ");");

}

void Preferences::setHighlightObjects(int state)
{
    _highlightObjects = state;
    ui->highlight->setCheckState((Qt::CheckState)state);
}

void Preferences::setHighlightTime(int value)
{
    _highlightTime = value;
    ui->highlightTimeSpinBox->setValue(value);
}

void Preferences::setHighlightRate(int value)
{
    _highlightRate = value;
    ui->highlightRateSpinBox->setValue(value);
}

void Preferences::abort()
{
    emit changeBackgroundColor(_backgroundColor);
    emit showObjectIds        (_showObjectIds);
    emit showCoordinates      (_showCoordinates);
    emit showVectors          (_showVectors);

    emit changeHighlightColor(_highlightColor);
    emit showHighlightObjects(_highlightObjects);
    emit changeHighlightTime (_highlightTime);
    emit changeHighlightRate (_highlightRate);
}
