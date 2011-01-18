#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

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
    Ui::MainWindow *ui;
    GLWidget * _view;

private slots:
    void on_actionAboutQt_triggered();
    void on_actionAbout_3DVV_triggered();
    void on_actionOpen_object_file_triggered();
};

#endif // MAINWINDOW_H
