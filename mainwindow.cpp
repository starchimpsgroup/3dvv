#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _view = new GLWidget(this);
    ui->gridLayout->addWidget(_view,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionXML_Datei_laden_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "File open", QApplication::applicationDirPath(), "All files (*.*)");
}
