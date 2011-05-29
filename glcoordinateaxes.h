/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLCOORDINATEAXES_H
#define GLCOORDINATEAXES_H

#include <qgl.h>
#include <glcolor.h>
#include "glvector.h"

#define CYLINDERHEIGHT 0.3

//! The Coordinate Axes class.
/*!
    This class shows the coordinate axes X,Y and Z.
 */
class GLCoordinateAxes
{
private:
    //! The range of the Coordinate Axes.
    /*!
        This struct contains the beginning and the end of the coordinate axes.
        This struct can also be used for scale the coordinate axes, in the future.
     */
    struct range
    {
     float rangeBegin; //!< The beginning of the coordinate axe
     float rangeEnd;   //!< The end of the coordinate axe
    };

public:
    typedef struct range Range; //! The range of the Coordinate Axes.

    //! Constructor of the coordinate axes.
    /*!
        Initialize with the standard range of the axes and a standard color.
        \see GLCoordinateAxes::Range
        \see GLColor
     */
    GLCoordinateAxes();

    //! Constructor of the coordinate axes.
    /*!
        Initialize with the range of the axes and a standard color.
        \param rangeX X-axe range
        \param rangeY Y-axe range
        \param rangeZ Z-axe range
        \see GLCoordinateAxes::Range
        \see GLColor
     */
    GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                      const GLCoordinateAxes::Range &rangeY,
                      const GLCoordinateAxes::Range &rangeZ );

    //! Constructor of the coordinate axes.
    /*!
        Initialize with the range of the axes and a color for each of them.
        \param rangeX X-axe range
        \param rangeY Y-axe range
        \param rangeZ Z-axe range
        \param colorX X-axe color
        \param colorY Y-axe color
        \param colorZ Z-axe color
        \see GLCoordinateAxes::Range
        \see GLColor
     */
    GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                      const GLCoordinateAxes::Range &rangeY,
                      const GLCoordinateAxes::Range &rangeZ,
                      const GLColor &colorX,
                      const GLColor &colorY,
                      const GLColor &colorZ );

    //! Draw coordinate axes.
    /*!
        Draw coordinate axes with numbers on every second peak.
     */
    void draw();

    //! Set default colors.
    /*!
        Set the default colors for every axe.
     */
    void setDefaultColors();

    //! Set colors.
    /*!
        Set colors for every axe.
        \param colorX X-axe color
        \param colorY Y-axe color
        \param colorZ Z-axe color
        \see GLColor
     */
    void setColors( const GLColor &colorX,
                    const GLColor &colorY,
                    const GLColor &colorZ );

    //! Set ranges.
    /*!
        Set ranges for every axe.
        \param rangeX X-axe range
        \param rangeY Y-axe range
        \param rangeZ Z-axe range
        \see GLCoordinateAxes::Range
     */
    void setRanges( const GLCoordinateAxes::Range &rangeX,
                    const GLCoordinateAxes::Range &rangeY,
                    const GLCoordinateAxes::Range &rangeZ);

private:
    //! Draw cylinder.
    /*!
        Draws a cylinder with a peak in a specific position and rotation.
        \param point Position of cylinder
        \param around Direction for rotation
        \param angle Angle to rotate
        \see GLVector
     */
    void drawCylinder( const GLVector &point, const GLVector &around, GLfloat angle );

    //! Draw distance marker.
    /*!
        Draws distance marker on every full number and draws the number under every second marker.
     */
    void drawDistanceMarker();

private:
    Range _rangeX;   //!< X-axe range
    Range _rangeY;   //!< Y-axe range
    Range _rangeZ;   //!< Z-axe range
    GLColor _colorX; //!< X-axe color
    GLColor _colorY; //!< Y-axe color
    GLColor _colorZ; //!< Z-axe color
};

#endif // GLCOORDINATEAXES_H
