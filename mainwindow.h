/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "glwidget.h"
#include "navigation.h"
#include "preferences.h"
#include "settings.h"
#include "navigationlabel.h"

#define TIMERANGE 32

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow   * ui;
    GLWidget         * _view;
    Navigation       * _navigation;
    Preferences      * _preferences;
    Settings         * _settings;
    NavigationLabel  * _navigationLabel;

    int                _time;
    int                _timeMax;
    int                _timeID;
    int                _objectPos;
    int                _objectPosSave;

    bool               _highlightObjects;
    int                _highlightTime;
    int                _highlightRate;

    QList<GLObject *>  _objects;

private:
    void updateIndex();
    int  time(){ return _timeMax + _highlightTime; }
    void updateStatusBar();
    //static bool caseInsensitiveLessThanTime(const GLObject * objectA, const GLObject * objectB);

private slots:
    void on_actionAboutQt_triggered();
    void on_actionAbout_3DVV_triggered();
    void on_actionOpen_object_file_triggered();
    void on_actionPreferences_triggered();
    void on_actionNavigation_triggered(){_navigationLabel->changeStatus();}
    void on_actionReset_camera_position_triggered(){ _view->reset(); }
    void on_actionScript_start_triggered();
    void on_actionScript_end_triggered();

    void openNavigation(bool open);
    void changeBackgroundColor(GLColor color);
    void showObjectIds(int state);
    void showCoordinates(int state);
    void showVectors(int state);

    void showHighlightObjects(int state);
    void changeHighlightColor(GLColor color);
    void changeHighlightTime(int value);
    void changeHighlightRate(int value);

    void play(bool value);
    void setTime(int time);
    void step(int value);

protected:
    void timerEvent(QTimerEvent *);
};

#endif // MAINWINDOW_H
