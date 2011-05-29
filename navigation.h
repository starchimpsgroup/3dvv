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

//! The Navigation class.
/*!
    This class shows a navigation to control the script.
 */
class Navigation : public QWidget
{
    Q_OBJECT

public:
    //! Constructor of the Navigation class.
    /*!
        \param parent Parent of the widget
     */
    explicit Navigation(QWidget *parent = 0);

    //! Destructor of the Navigation class.
    ~Navigation();

    //! Set the pause value and the play icon.
    void pause();

    //! Set slider maximum.
    /*!
        \param max Maximum of the slider
     */
    void setSliderMaximum (int max);

    //! Set slider position.
    /*!
        \param pos Position of the slider
     */
    void setSliderPosition(int pos);

private:
    Ui::Navigation * ui;         //!< The ui
    bool             _play;      //!< Play value

private slots:
    void on_playPause_clicked(); //!< Play/Pause button event
    void on_previous_clicked();  //!< Previous event
    void on_next_clicked();      //!< Next event
    void sliderMoved(int value); //!< Slider moved value changed \param value Slider position

signals:
    void play(bool);             //!< Send the play value
    void positionChanged(int);   //!< Send the slider position
    void step(int);              //!< Send the script step
};

#endif // NAVIGATION_H
