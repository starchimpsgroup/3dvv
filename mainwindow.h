/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"
#include "navigation.h"
#include "preferences.h"
#include "settings.h"

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

    int                _time;
    int                _timeMax;
    int                _timeID;
    int                _objectPos;
    int                _objectPosSave;

    QList<GLObject *>  _objects;

private:
    void updateIndex();

private slots:
    void on_actionAboutQt_triggered();
    void on_actionAbout_3DVV_triggered();
    void on_actionOpen_object_file_triggered();
    void on_actionPreferences_triggered();

    void openNavigation(bool open);
    void changeBackgroundColor(GLColor color);

    void play(bool);
    void setTime(int time);

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
