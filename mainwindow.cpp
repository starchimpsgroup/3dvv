#include "mainwindow.h"
#include "ui_mainwindow.h"

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
