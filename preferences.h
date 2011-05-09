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
    void setShowObjectIds(int state);
    void setShowCoordinates(int state);
    void setShowVectors(int state);

private:
    Ui::Preferences * ui;
    QColorDialog    * _backgroundColorDialog;
    GLColor           _backgroundColor;
    int               _showObjectIds;
    int               _showCoordinates;
    int               _showVectors;

private slots:
    void on_backgroundColorButton_clicked();
    void on_ids_stateChanged(int state);
    void on_coordinates_stateChanged(int state);
    void on_vectors_stateChanged(int state);
    void abort();

signals:
    void changeBackgroundColor(GLColor);
    void showObjectIds(int);
    void showCoordinates(int);
    void showVectors(int);
};

#endif // PREFERENCES_H
