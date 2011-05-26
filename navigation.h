/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QWidget>

namespace Ui {
    class Navigation;
}

class Navigation : public QWidget
{
    Q_OBJECT

public:
    explicit Navigation(QWidget *parent = 0);
    ~Navigation();

    void pause();
    void setSliderMaximum (int max);
    void setSliderPosition(int pos);

private:
    Ui::Navigation * ui;
    bool             _play;

private slots:
    void on_playPause_clicked();
    void on_previous_clicked();
    void on_next_clicked();
    void sliderMoved(int value);

signals:
    void play(bool);
    void positionChanged(int);
    void step(int);
};

#endif // NAVIGATION_H
