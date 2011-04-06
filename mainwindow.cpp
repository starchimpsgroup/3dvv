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

    QCoreApplication::setOrganizationName  ("Fachhochschule Südwestfalen");
    QCoreApplication::setOrganizationDomain("fh-swf.de");
    QCoreApplication::setApplicationName   ("3D Vector Viewer");

    _settings    = new Settings("Fachhochschule Südwestfalen", "3D Vector Viewer");

    _view        = new GLWidget(_settings->backgroundColor(), this);
    _navigation  = new Navigation(this);
    _preferences = new Preferences(this);

    QObject::connect(_preferences, SIGNAL(changeBackgroundColor(GLColor)), this, SLOT(changeBackgroundColor(GLColor)));

    _navigation->setVisible(false);

    NavigationLabel * label = new NavigationLabel(this);
    QObject::connect(label, SIGNAL(pressed(bool)), this, SLOT(openNavigation(bool)));

    ui->statusBar->addPermanentWidget(label);

    ui->viewLayout->addWidget(_view);
    ui->gridLayout->addWidget(_navigation);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _view;
    delete _navigation;
    delete _preferences;
    delete _settings;
}

void MainWindow::openNavigation(bool open)
{
    _navigation->setVisible(open);
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
    _preferences->exec();
}

void MainWindow::changeBackgroundColor(GLColor color)
{
    _settings->setBackgroundColor(color);
    _view->setBackgroundColor(color);
}
