/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLPLANE_H
#define GLPLANE_H

#include "globject.h"
#include "glvector.h"

//! The Plane class.
/*!
    This class shows a plane on a point with a normal vector.
 */
class GLPlane : public GLObject
{
public:
    //! Constructor of the GLPlane class with a point and a normal vector.
    /*!
        Initialize with the two vectors.
        \param point Vector for plane position
        \param normal Normal vector
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLVector
        \see GLColor
     */
    GLPlane(GLVector point, GLVector normal, GLColor color, QString objectID, int time);

    //! Return the vector of the plane position.
    /*!
        \return Vector of the position
        \see GLVector
     */
    GLVector point(){ return _point; }

    //! Return the vector of the normal vector.
    /*!
        \return Vector of the normal
        \see GLVector
     */
    GLVector normal(){ return _normal; }

    //! The plane fromXML method is used to fetch specified tags from the XML-File.
    /*!
        This method fetches a specified amount of tags, the most important being:

        -# The id.
        -# Two points.
        -# The color.
        -# The time in msec.
        \param object XML object
        \return Pointer of new plane object
     */
    static GLPlane * fromXml(const QDomElement &object);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();

private:
    GLVector _normal; //!< Normal vector \see GLVector
    GLVector _point;  //!< Point vector \see GLVector
};

#endif // GLPLANE_H
