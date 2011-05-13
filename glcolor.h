/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef GLCOLOR_H
#define GLCOLOR_H

#include <QColor>

//! The Color class.
/*!
    This class contains the values of a color.
 */
class GLColor
{
public:
    //! Constructor of thr GLColor class without parameters.
    /*!
        Initialize with the standard color black.
     */
    GLColor();

    //! Constructor of thr GLColor class with color parameters.
    /*!
        Initialize with the input colors and alpha in float.
        Input range 0.0f to 1.0f.
        \param redF color
        \param greenF color
        \param blueF color
        \param alphaF value
     */
    GLColor( float redF, float greenF, float blueF, float alphaF = 1.0f );

    //! Constructor of thr GLColor class with color parameters.
    /*!
        Initialize with the input colors and alpha in integer.
        Input range 0 to 255.
        \param redI color
        \param greenI color
        \param blueI color
        \param alphaI value
     */
    GLColor( int redI, int greenI, int blueI, int alphaI = 255 );

    //! Constructor of thr GLColor class with QColor parameter.
    /*!
        Initialize with colors and alpha in QColor.
        Input range 0 to 255.
        \param data QChar
     */
    GLColor( QColor color );

    //! Return red color of the color.
    /*!
        \see _red
        \return red color float
     */
    float redF()  { return _red; }

    //! Return green color of the color.
    /*!
        \see _green
        \return green color float
     */
    float greenF(){ return _green; }

    //! Return blue color of the color.
    /*!
        \see _blue
        \return blue color float
     */
    float blueF() { return _blue; }

    //! Return alpha value of the color.
    /*!
        \see _alpha
        \return alpha value float
     */
    float alphaF() { return _alpha; }

    int redDez()  { return _red   * 255.0; }

    int greenDez(){ return _green * 255.0; }

    int blueDez() { return _blue  * 255.0; }

    int alphaDez(){ return _alpha * 255.0; }

    /*!
        Set the colors and standard alphain float.
        \param redF color
        \param greenF color
        \param blueF color
        \param alphaF value
     */
    void setColorsF(float redF, float greenF, float blueF, float alphaF = 1.0f){_red   = redF;
                                                                                _green = greenF;
                                                                                _blue  = blueF;
                                                                                _alpha = alphaF;}

    void setRedF  (float redF)  { _red   = redF; }
    void setGreenF(float greenF){ _green = greenF; }
    void setBlueF (float blueF) { _blue  = blueF; }
    void setAlphaF(float alphaF){ _alpha = alphaF; }

    const QColor qcolor();

    bool isTransparent(){ return _alpha != 1.0f; }

private:
    float _red;     //!< Red Color
    float _green;   //!< Green Color
    float _blue;    //!< Blue Color
    float _alpha;   //!< Alpha Value
};

#endif // GLCOLOR_H
