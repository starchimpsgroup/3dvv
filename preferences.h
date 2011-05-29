/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QColorDialog>
#include "glcolor.h"

namespace Ui {
    class Preferences;
}

//! The Preferences class.
/*!
    This class shows a preferences window.
 */
class Preferences : public QDialog
{
    Q_OBJECT

public:
    //! Constructor of the Preferences class.
    /*!
        \param parent Parent of the widget
     */
    explicit Preferences(QWidget *parent = 0);

    //! Destructor of the Preferences class.
    ~Preferences();

    //! Set background color button color.
    /*!
        \param color Color of the button
        \param save Value to save the color
     */
    void setBackgroundColorButtonColor(GLColor color, bool save = true);

    //! Set show object ids.
    /*!
        State to draw the object ids in the 3D view.
        \param state State of object ids
     */
    void setShowObjectIds(int state);

    //! Set show coordinates.
    /*!
        State to draw the object coordinates in the 3D view.
        \param state State of coordinates
     */
    void setShowCoordinates(int state);

    //! Set show vectors.
    /*!
        State to draw the object vectors in the 3D view.
        \param state State of vectors
     */
    void setShowVectors(int state);

    //! Set highlight color button color.
    /*!
        Set color for highlight color button.
        \param color Color of the button
        \param save Value to save the color
     */
    void setHighlightColorButtonColor(GLColor color, bool save = true);

    //! Set highlight objects.
    /*!
        State to highlight new objects.
        \param state State of highlighting
     */
    void setHighlightObjects(int state);

    //! Set highlight time.
    /*!
        Time to highlight new objects.
        \param value Milliseconds of the time to highlight the object
     */
    void setHighlightTime(int value);

    //! Set highlight rate.
    /*!
        Rate to highlight new objects.
        \param value How often the object is highlighted
     */
    void setHighlightRate(int value);

private:
    Ui::Preferences * ui;                     //!< The ui
    QColorDialog    * _backgroundColorDialog; //!< Background color dialog
    GLColor           _backgroundColor;       //!< Background color
    int               _showObjectIds;         //!< Object ids value
    int               _showCoordinates;       //!< Coordinates value
    int               _showVectors;           //!< Vectors value

    QColorDialog    * _highlightColorDialog;  //!< Highlight color dialog
    int               _highlightObjects;      //!< Highlight objects
    GLColor           _highlightColor;        //!< Highlight color
    int               _highlightTime;         //!< Highlight time
    int               _highlightRate;         //!< Highlight rate

private slots:
    void on_backgroundColorButton_clicked();          //!< Background color button clicked
    void on_ids_stateChanged(int state);              //!< Ids state changed \param State of drawing ids in 3D view
    void on_coordinates_stateChanged(int state);      //!< Coordinates state changed \param State of drawing coordinates in 3D view
    void on_vectors_stateChanged(int state);          //!< Vectors state changed \param State of drawing vectors in 3D view

    void on_highlightColorButton_clicked();           //!< Highlight color button clicked
    void on_highlight_stateChanged(int state);        //!< Highlight state changed \param State of highlighting objects in 3D view
    void on_highlightTimeSpinBox_valueChanged(int i); //!< Highlight time changed \param State of highlightinging time
    void on_highlightRateSpinBox_valueChanged(int i); //!< Highlight rate changed \param State of highlightinging rate

    void abort();                                     //!< Abort all changes of the preferences

signals:
    void changeBackgroundColor(GLColor);              //!< Send new background color
    void showObjectIds(int);                          //!< Send object ids value
    void showCoordinates(int);                        //!< Send coordinates value
    void showVectors(int);                            //!< Send vectors value

    void changeHighlightColor(GLColor);               //!< Send new highlight color value
    void showHighlightObjects(int);                   //!< Send highlight objects value
    void changeHighlightTime(int);                    //!< Send highlight time value
    void changeHighlightRate(int);                    //!< Send highlight rate value
};

#endif // PREFERENCES_H
