/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLLINE_H
#define GLLINE_H

#include "globject.h"
#include "glvector.h"

//! The Line class.
/*!
    This class shows a line crossing two points.
 */
class GLLine : public GLObject
{
public:
    //! Constructor of the GLLine class with two vectors.
    /*!
        Initialize with the two vectors.
        \param point Vector
        \param direction Vector
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLVector
        \see GLColor
     */
    GLLine( GLVector point, GLVector direction, GLColor color, QString objectID, int time );

    //! Return the vector of the line.
    /*!
        \return Vector of the line
        \see GLVector
     */
    GLVector line(){ return _line; }

    //! The line fromXML method is used to fetch specified tags from the XML-File.
    /*!
        This method fetches a specified amount of tags, the most important being:

        -# The id.
        -# Two points.
        -# The color.
        -# The time in msec.
        \param object XML object
        \return Pointer of new line object
     */
    static GLLine * fromXml(const QDomElement &object);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();
    void glVector();

private:
    GLVector _line; //!< Line vector \see GLVector
};

#endif // GLLINE_H
