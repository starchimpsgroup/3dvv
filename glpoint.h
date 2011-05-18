#ifndef GLPOINT_H
#define GLPOINT_H

#include "qgl.h"
#include "globject.h"

class GLPoint : public GLObject
{
public:
    GLPoint( GLColor color = GLColor(), QString objectID = "", int time = 0 );
    GLPoint( GLdouble x, GLdouble y, GLdouble z, GLColor color = GLColor(), QString objectID = "", int time = 0 );

    GLdouble x(){ return _x; }
    GLdouble y(){ return _y; }
    GLdouble z(){ return _z; }

    /*!
        \brief The point fromXML method is used to fetch specified tags from the XML-File.

        This method fetches a specified amount of tags , the most important being:

        \list
            \i id.
            \i one points.
            \i The color.
            \i The time.
        \endlist
     */
    static GLPoint* fromXml(const QDomElement &object);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();

private:
    GLdouble _x;
    GLdouble _z;
    GLdouble _y;
};

#endif // GLPOINT_H
