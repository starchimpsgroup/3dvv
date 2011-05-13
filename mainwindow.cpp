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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QPicture>
#include "navigationlabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName  ("FH-SWF");
    QCoreApplication::setOrganizationDomain("fh-swf.de");
    QCoreApplication::setApplicationName   ("3D Vector Viewer");

    _settings    = new Settings();

    _view        = new GLWidget(_settings->backgroundColor(),
                                _settings->showObjectIds(),
                                _settings->showCoordinates(),
                                _settings->showVectors(),
                                this);

    _navigation  = new Navigation(this);
    _preferences = new Preferences(this);

    QObject::connect(_preferences, SIGNAL(changeBackgroundColor(GLColor)), this, SLOT(changeBackgroundColor(GLColor)));
    QObject::connect(_preferences, SIGNAL(showCoordinates(int)),           this, SLOT(showCoordinates(int)));
    QObject::connect(_preferences, SIGNAL(showObjectIds(int)),             this, SLOT(showObjectIds(int)));
    QObject::connect(_preferences, SIGNAL(showVectors(int)),               this, SLOT(showVectors(int)));
    QObject::connect(_navigation,  SIGNAL(play(bool)),                     this, SLOT(play(bool)));
    QObject::connect(_navigation,  SIGNAL(positionChanged(int)),           this, SLOT(setTime(int)));
    QObject::connect(_navigation,  SIGNAL(step(int)),                      this, SLOT(step(int)));

    NavigationLabel * label = new NavigationLabel(this);
    QObject::connect(label, SIGNAL(pressed(bool)), this, SLOT(openNavigation(bool)));

    ui->statusBar->addPermanentWidget(label);

    setCentralWidget(_view);
    ui->mainToolBar->addWidget(_navigation);
    ui->mainToolBar->setVisible(false);

    _timeMax = _time = _objectPos = 0;
    _timeID  = -1;

    // Input

    QList<GLObject *>  datei;
    GLObject * vec;

    // Point
    vec = new GLPoint(2.0f,2.0f,2.0f,GLColor(1.0f,0.0f,0.0f),"Point", 0);
    datei.append(vec);

    vec = new GLPoint(-2.0f,2.0f,2.0f,GLColor(1.0f,0.0f,0.0f),"(Point1111\n1\n2\n3\n4\n5\n6)", 0);
    datei.append(vec);


    vec = new GLPlain(GLVector(-5,-6,-4),
                      GLVector(-1,-0,-0),
                      GLColor(100,50,0,125),
                      "Plain",
                      0);
    datei.append(vec);

    vec = new GLPlain(GLVector(-5,6,4),
                      GLVector(1,0,0),
                      GLColor(100,50,0,125),
                      "Plain",
                      0);
    datei.append(vec);

    vec = new GLPlain(GLVector(-5,-6,-4),
                      GLVector(-5,-3,-1),
                      GLColor(0,255,0,125),
                      "Plain",
                      0);
    datei.append(vec);

    vec = new GLPlain(GLVector(5,6,4),
                      GLVector(5,3,1),
                      GLColor(0,255,0,125),
                      "Plain",
                      0);
    datei.append(vec);

    vec = new GLPlain(GLVector(3.0,3.0,3.0),
                      GLVector(4.0,-3.0,4.0),
                      GLColor(0,255,0,125),
                      "Plain",
                      0);
    datei.append(vec);

    vec = new GLPlain(GLVector(-3.0,-3.0,-3.0),
                      GLVector(-4.0,-3.0,-4.0),
                      GLColor(0,255,0,125),
                      "Plain",
                      0);
    datei.append(vec);

    vec = new GLPoint(2.0f,2.0f,4.0f,GLColor(1.0f,0.0f,0.0f),"TEST", 0);
    datei.append(vec);

    // E
    GLColor E(1.0f,0.0f,0.5f);

    vec = new GLVector(1,0,0,1,5,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(1,5,0,4,5,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(4,5,0,4,4,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(4,4,0,2,4,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(2,4,0,2,3,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(2,3,0,4,3,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(4,3,0,4,2,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(4,2,0,2,2,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(2,2,0,2,1,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(2,1,0,4,1,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(4,1,0,4,0,0,E,"E", 0);
    datei.append(vec);

    vec = new GLVector(4,0,0,1,0,0,E,"E", 0);
    datei.append(vec);

    // N
    GLColor N(1.0f,0.5f,0.0f);

    vec = new GLVector(5,0,0,5,5,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(5,5,0,6,5,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(6,5,0,7,2,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(7,2,0,7,5,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(7,5,0,8,5,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(8,5,0,8,0,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(8,0,0,7,0,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(7,0,0,6,3,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(6,3,0,6,0,0,N,"N", 1000);
    datei.append(vec);

    vec = new GLVector(6,0,0,5,0,0,N,"N", 1000);
    datei.append(vec);

    // D
    GLColor D(0.0f,0.5f,1.0f);

    vec = new GLVector(9,0,0,9,5,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(9,5,0,11,5,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(11,5,0,12,4,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(12,4,0,12,1,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(12,1,0,11,0,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(11,0,0,9,0,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(10,1,0,10,4,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(10,4,0,11,4,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(11,4,0,11,1,0,D,"D", 2000);
    datei.append(vec);

    vec = new GLVector(11,1,0,10,1,0,D,"D", 2000);
    datei.append(vec);

    // E2
    GLColor E2(0.5f,1.0f,0.0f);

    vec = new GLVector(13,0,0,13,5,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(13,5,0,16,5,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(16,5,0,16,4,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(16,4,0,14,4,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(14,4,0,14,3,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(14,3,0,16,3,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(16,3,0,16,2,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(16,2,0,14,2,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(14,2,0,14,1,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(14,1,0,16,1,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(16,1,0,16,0,0,E2,"E2", 3000);
    datei.append(vec);

    vec = new GLVector(16,0,0,13,0,0,E2,"E2", 3000);
    datei.append(vec);

    foreach(GLObject * vec, datei)
    {
        _objects.append(vec);

        if(_timeMax < vec->time())
            _timeMax = vec->time();
    }

    // Input

    _navigation->setSliderMaximum(_timeMax);
    _view->setObjects(&_objects);

    updateIndex();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _view;
    delete _navigation;
    delete _preferences;
    delete _settings;
}

void MainWindow::step(int value)
{
    if(_objectPos + value >= 0 && _objectPos + value < _objects.size())
    {
        _view->setObjectIndex(_objectPos += value);
        _view->repaint();
        _navigation->setSliderPosition(_time = _objects.at(_objectPos)->time());
    }
}

void MainWindow::setTime(int time)
{
    _time = time;
    updateIndex();
}

void MainWindow::updateIndex()
{
    _objectPosSave = _objectPos;
    for(_objectPos = 0; _objectPos < _objects.size(); _objectPos++)
    {
        if(_time >= _objects.at(_objectPos)->time())
        {
            _view->setObjectIndex(_objectPos);
        }
        else
        {
            _objectPos--;
            break;
        }
    }

    if(_objectPosSave != _objectPos)
        _view->repaint();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    _time += TIMERANGE;

    updateIndex();

    _navigation->setSliderPosition(_time);

    if(_time >= _timeMax)
    {
        killTimer(_timeID);
        _timeID = -1;
        _navigation->pause();
    }
}

void MainWindow::openNavigation(bool open)
{
    ui->mainToolBar->setVisible(open);
}

void MainWindow::on_actionOpen_object_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "File open", QApplication::applicationDirPath(), "All files (*.*)");
}

void MainWindow::on_actionAbout_3DVV_triggered()
{
    QMessageBox::about(this, tr("About 3DVV"),
            tr("<b>3D Vector Viewer</b><br/>"
               "Copyright &copy; 2011 Fachhochschule S&uuml;dwestfalen<br/>"
               "Written by Christian Ernst and Kai Wellmann"));
}

void MainWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionPreferences_triggered()
{
    _preferences->setBackgroundColorButtonColor(_settings->backgroundColor());
    _preferences->setShowObjectIds(_settings->showObjectIds());
    _preferences->setShowCoordinates(_settings->showCoordinates());
    _preferences->setShowVectors(_settings->showVectors());
    _preferences->exec();
}

void MainWindow::changeBackgroundColor(GLColor color)
{
    _settings->setBackgroundColor(color);
    _view->setBackgroundColor(color);
}

void MainWindow::showObjectIds(int state)
{
    _settings->setShowObjectIds(state);
    _view->setShowObjectIds(state);
}

void MainWindow::showCoordinates(int state)
{
    _settings->setShowCoordinates(state);
    _view->setShowCoordinates(state);
}

void MainWindow::showVectors(int state)
{
    _settings->setShowVectors(state);
    _view->setShowVectors(state);
}

void MainWindow::play(bool value)
{
    if(value && _timeID == -1)
    {
        _timeID = startTimer(TIMERANGE);
    }
    else if(!value && _timeID != -1)
    {
        killTimer(_timeID);
        _timeID = -1;
    }
}
