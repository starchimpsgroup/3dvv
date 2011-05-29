/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLPOINT_H
#define GLPOINT_H

#include "qgl.h"
#include "globject.h"

//! The Point class.
/*!
    This class shows a point.
 */
class GLPoint : public GLObject
{
public:
    //! Constructor of the GLPoint class with a point.
    /*!
        Initialize with the two vectors.
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLColor
     */
    GLPoint( GLColor color = GLColor(), QString objectID = "", int time = 0 );

    //! Constructor of the GLPoint class with a point.
    /*!
        Initialize with the two vectors.
        \param x Position on x axe
        \param y Position on y axe
        \param z Position on z axe
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLColor
     */
    GLPoint( GLdouble x, GLdouble y, GLdouble z, GLColor color = GLColor(), QString objectID = "", int time = 0 );

    //! Return the x position.
    /*!
        \return Position on x axe
     */
    GLdouble x(){ return _x; }

    //! Return the y position.
    /*!
        \return Position on y axe
     */
    GLdouble y(){ return _y; }

    //! Return the z position.
    /*!
        \return Position on z axe
     */
    GLdouble z(){ return _z; }

    //! The point fromXML method is used to fetch specified tags from the XML-File.
    /*!
        This method fetches a specified amount of tags, the most important being:

        -# The id.
        -# Two points.
        -# The color.
        -# The time in msec.
        \param object XML object
        \return Pointer of new point object
     */
    static GLPoint* fromXml(const QDomElement &object);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();

private:
    GLdouble _x; //!< Position on x axe
    GLdouble _z; //!< Position on y axe
    GLdouble _y; //!< Position on z axe
};

#endif // GLPOINT_H
