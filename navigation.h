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
    void sliderMoved(int value);

signals:
    void play(bool);
    void positionChanged(int);
};

#endif // NAVIGATION_H
