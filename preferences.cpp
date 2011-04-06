#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(rejected()), this, SLOT(abort()));
    _backgroundColorDialog = new QColorDialog(this);
}

Preferences::~Preferences()
{
    delete _backgroundColorDialog;
    delete ui;
}

void Preferences::on_backgroundColorButton_clicked()
{
    _backgroundColorDialog->exec();
    QColor selectedColor  = _backgroundColorDialog->selectedColor();
    setBackgroundColorButtonColor(selectedColor, false);

    emit changeBackgroundColor(selectedColor);
}

void Preferences::setBackgroundColorButtonColor(GLColor color, bool save)
{
    if(save)
        _backgroundColor = color;

    ui->backgroundColorButton->setStyleSheet("background-color: rgb(" + QString::number(color.redDez()) + ", "
                                                                      + QString::number(color.greenDez()) + ", "
                                                                      + QString::number(color.blueDez()) + ");");
}

void Preferences::abort()
{
    emit changeBackgroundColor(_backgroundColor);
}
