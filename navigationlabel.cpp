#include "navigationlabel.h"

NavigationLabel::NavigationLabel(QWidget *parent) :
    QLabel(parent), _pressed(false)
{
    setPixmap(QPixmap(":/navigation/navigation_up.png"));
}

void NavigationLabel::mousePressEvent( QMouseEvent * ev )
{
    if(_pressed)
    {
        setPixmap(QPixmap(":/navigation/navigation_up.png"));
        _pressed = false;
        emit pressed(_pressed);

    }
    else
    {
        setPixmap(QPixmap(":/navigation/navigation_down.png"));
        _pressed = true;
        emit pressed(_pressed);
    }
}
