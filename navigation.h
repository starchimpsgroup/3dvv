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

private:
    Ui::Navigation *ui;
};

#endif // NAVIGATION_H
