/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLPLANE_H
#define GLPLANE_H

#include "globject.h"
#include "glvector.h"

class GLPlane : public GLObject
{
public:
    GLPlane(GLVector point, GLVector normal, GLColor color, QString objectID, int time);

    GLVector point(){ return _point; }
    GLVector normal(){ return _normal; }

    //! The plane fromXML method is used to fetch specified tags from the XML-File.
    /*!
        This method fetches a specified amount of tags, the most important being:

        -# The id.
        -# Two points.
        -# The color.
        -# The time.
        \param object XML object
        \return Pointer of new plane object
     */
    static GLPlane * fromXml(const QDomElement &object);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();

private:
    GLVector _normal;
    GLVector _point;
};

#endif // GLPLANE_H
