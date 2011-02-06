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
        Initialize with the input colors and standard alpha.
        \param red color
        \param green color
        \param blue color
     */
    GLColor( float redF, float greenF, float blueF );

    //! Constructor of thr GLColor class with color parameters.
    /*!
        Initialize with the input colors and alpha.
        \param red color
        \param green color
        \param blue color
        \param alpha value
     */
    GLColor( float redF, float greenF, float blueF, float alphaF );

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
    float alpaF() { return _alpha; }

private:
    float _red;     //!< Red Color
    float _green;   //!< Green Color
    float _blue;    //!< Blue Color
    float _alpha;   //!< Alpha Value
};

#endif // GLCOLOR_H
