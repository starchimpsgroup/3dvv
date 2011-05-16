#include "navigationlabel.h"

NavigationLabel::NavigationLabel(QWidget *parent) :
    QLabel(parent), _pressed(false)
{
    setPixmap(QPixmap(":/navigation/navigation_up.png"));
}

void NavigationLabel::changeStatus()
{
    if(_pressed)
    {
        setPixmap(QPixmap(":/navigation/navigation_up.png"));
        _pressed = false;
    }
    else
    {
        setPixmap(QPixmap(":/navigation/navigation_down.png"));
        _pressed = true;
    }

    emit pressed(_pressed);
}
