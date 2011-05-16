#ifndef NAVIGATIONLABEL_H
#define NAVIGATIONLABEL_H

#include <QLabel>
#include <QWidget>

class NavigationLabel : public QLabel
{
    Q_OBJECT

public:
    NavigationLabel(QWidget *parent = 0);
    void changeStatus();

private:
    void mousePressEvent(QMouseEvent *){ changeStatus(); };

private:
    bool _pressed;

signals:
    void pressed(bool);
};

#endif // NAVIGATIONLABEL_H
