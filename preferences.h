#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QColorDialog>
#include "glcolor.h"

namespace Ui {
    class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();

    void setBackgroundColorButtonColor(GLColor color, bool save = true);

private:
    Ui::Preferences * ui;
    QColorDialog    * _backgroundColorDialog;
    GLColor           _backgroundColor;

private slots:
    void on_backgroundColorButton_clicked();
    void abort();

signals:
    void changeBackgroundColor(GLColor);
};

#endif // PREFERENCES_H
