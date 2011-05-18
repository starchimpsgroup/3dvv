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

    void setHighlightColorButtonColor(GLColor color, bool save = true);
    void setHighlightObjects(int state);
    void setHighlightTime(int value);
    void setHighlightRate(int value);

private:
    Ui::Preferences * ui;
    QColorDialog    * _backgroundColorDialog;
    GLColor           _backgroundColor;
    int               _showObjectIds;
    int               _showCoordinates;
    int               _showVectors;

    QColorDialog    * _highlightColorDialog;
    int               _highlightObjects;
    GLColor           _highlightColor;
    int               _highlightTime;
    int               _highlightRate;

private slots:
    void on_backgroundColorButton_clicked();
    void on_ids_stateChanged(int state);
    void on_coordinates_stateChanged(int state);
    void on_vectors_stateChanged(int state);

    void on_highlightColorButton_clicked();
    void on_highlight_stateChanged(int state);
    void on_highlightTimeSpinBox_valueChanged(int i);
    void on_highlightRateSpinBox_valueChanged(int i);

    void abort();

signals:
    void changeBackgroundColor(GLColor);
    void showObjectIds(int);
    void showCoordinates(int);
    void showVectors(int);

    void changeHighlightColor(GLColor);
    void showHighlightObjects(int);
    void changeHighlightTime(int);
    void changeHighlightRate(int);
};

#endif // PREFERENCES_H
