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

//! The Main Window class.
/*!
    This class contains the 3D view and all other widgets, like the navigation and the preferences.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor of the MainWindow class.
    /*!
        Initialize application, with witgets, connections and settings.
        \param parent Parent of the window
     */
    explicit MainWindow(QWidget *parent = 0);

    //! Destructor of the MainWindow class.
    ~MainWindow();

private:
    Ui::MainWindow   * ui;                //!< The ui
    GLWidget         * _view;             //!< The 3D view
    Navigation       * _navigation;       //!< The script navigation
    Preferences      * _preferences;      //!< The preferences window
    Settings         * _settings;         //!< The settings
    NavigationLabel  * _navigationLabel;  //!< The navigation label, to show the navigation

    int                _time;             //!< The actually time
    int                _timeMax;          //!< The maximum time
    int                _timeID;           //!< The id of the timer
    int                _objectPos;        //!< The actually object position
    int                _objectPosSave;    //!< The saved object position

    bool               _highlightObjects; //!< The highlight objects status
    int                _highlightTime;    //!< The highlight time value
    int                _highlightRate;    //!< The highlight rate value

    QList<GLObject *>  _objects;          //!< The list ob mathematic objects

private:
    //! Update index.
    /*!
        Compares the actually time and the objects to highlight the objects and give the 3D view the actually object position.
     */
    void updateIndex();

    //! Time.
    /*!
        \return The maximum of time
     */
    int  time(){ return _timeMax + _highlightTime; }

    //! Update status bar.
    void updateStatusBar();
    //static bool caseInsensitiveLessThanTime(const GLObject * objectA, const GLObject * objectB);

private slots:
    void on_actionAboutQt_triggered();                                      //!< About qt triggered
    void on_actionAbout_3DVV_triggered();                                   //!< About 3DVV triggered
    void on_actionOpen_object_file_triggered();                             //!< Open object file triggered
    void on_actionPreferences_triggered();                                  //!< Preferences triggered
    void on_actionNavigation_triggered(){_navigationLabel->changeStatus();} //!< Navigation triggered
    void on_actionReset_camera_position_triggered(){ _view->reset(); }      //!< Reset camera position triggered
    void on_actionScript_start_triggered();                                 //!< Script start triggered
    void on_actionScript_end_triggered();                                   //!< Script end triggered

    void openNavigation(bool open);                                         //!< Open navigation \param open Value to open or not
    void changeBackgroundColor(GLColor color);                              //!< Change background color \param color Color of background
    void showObjectIds(int state);                                          //!< Show object ids \param state State of show object ids
    void showCoordinates(int state);                                        //!< Show coordinates \param state State of show coordinates
    void showVectors(int state);                                            //!< Show vectors \param state State of show vectors

    void showHighlightObjects(int state);                                   //!< Show highlight objects \param state State of show highlight objects
    void changeHighlightColor(GLColor color);                               //!< Change highlight color \param color Color of highlighted objects
    void changeHighlightTime(int value);                                    //!< Change highlight time \param value Value of the time to highlight objects
    void changeHighlightRate(int value);                                    //!< Change highlight rate \param value Value of the rate to highlight objects in time

    void play(bool value);                                                  //!< Play \param value Value to play the script or not
    void setTime(int time);                                                 //!< Set time \param time The actually time
    void step(int value);                                                   //!< Step \param value Value of script step back or forward

protected:
    //! Update status bar.
    void timerEvent(QTimerEvent *);
};

#endif // MAINWINDOW_H
