/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef NAVIGATIONLABEL_H
#define NAVIGATIONLABEL_H

#include <QLabel>
#include <QWidget>

//! The Navigation Label class.
/*!
    This class shows a label for switching the navigation on and off.
 */
class NavigationLabel : public QLabel
{
    Q_OBJECT

public:
    //! Constructor of the NavigationLabel class.
    /*!
        \param parent Parent of the label
     */
    NavigationLabel(QWidget *parent = 0);

    //! Change status.
    /*!
        Changes the status of the label and emit a signal to turn the navigation off and on.
     */
    void changeStatus();

private:
    //! Mouse press event.
    /*!
        If the user pressed on this label the _pressed status will changed and the navigation will be tuned off or on.
        \see changeStatus
     */
    void mousePressEvent(QMouseEvent *){ changeStatus(); }

private:
    bool _pressed;      //!< Status of the label \see changeStatus

signals:
    void pressed(bool); //!< Signal to send the changed status \see changeStatus
};

#endif // NAVIGATIONLABEL_H
