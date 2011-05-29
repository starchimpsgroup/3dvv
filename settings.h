/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include "glcolor.h"

//! The Settings Label class.
/*!
    This class saves the settings from the preferences window.
    \see Preferences
 */
class Settings
{
public:
    //! Constructor of the Settings class.
    Settings();

    //! Synchronise settings / Save on system
    ~Settings();

    //! Set background color.
    /*!
        \param color Color of the background
        \see GLVector
     */
    void    setBackgroundColor(GLColor &color);

    //! Return background color.
    /*!
        \return Color of the Background
     */
    GLColor backgroundColor();

    //! Set state show object ids text.
    /*!
        \param state State of show object ids in 3D view
     */
    void setShowObjectIds(int state);

    //! Set state show coordinates text.
    /*!
        \param state State of show coordinates in 3D view
     */
    void setShowCoordinates(int state);

    //! Set state show vectors text.
    /*!
        \param state State of show vectors in 3D view
     */
    void setShowVectors(int state);

    //! Show object ids state.
    /*!
        \return State of show object ids
     */
    int  showObjectIds();

    //! Show coordinates text state.
    /*!
        \return State of show coordinates
     */
    int  showCoordinates();

    //! Show vectors text state.
    /*!
        \return State of show vectors
     */
    int  showVectors();

    //! Set highlight color.
    /*!
        \param color Highlight color
        \see GLVector
     */
    void    setHighlightColor(GLColor &color);

    //! Return highlight color.
    /*!
        \return Highlight color
     */
    GLColor highlightColor();

    //! Set highlight objects state.
    /*!
        \param state State of highlighting objects
     */
    void setHighlightObjects(int state);

    //! Set highlight time value.
    /*!
        Time how long the objects are highlighted
        \param value Value of highlighting time
     */
    void setHighlightTime(int value);

    //! Set highlight rate value.
    /*!
        Rate how often the objects are hightlighted
        \param value Value of highlighting rate
     */
    void setHighlightRate(int value);

    //! Return highlight objects state.
    /*!
        \return State of highlight objects
     */
    int  highlightObjects();

    //! Return highlight time value.
    /*!
        \return Value of highlight time
     */
    int  highlightTime();

    //! Return highlight rate value.
    /*!
        \return Value of highlight rate
     */
    int  highlightRate();

    //! Set window geometry.
    /*!
        \param array Window geometry values
     */
    void storeGeometry(QByteArray array);

    //! Return window geometry.
    /*!
        \return Window geometry values
     */
    QByteArray restoreGeometry();

private:
    QSettings * _settings; //!< Settings
};

#endif // SETTINGS_H
