#ifndef GLPLANE_H
#define GLPLANE_H

#include "globject.h"
#include "glvector.h"

class GLPlane : public GLObject
{
public:
    GLPlane(GLVector point, GLVector normal, GLColor color, QString objectID, int time);

    /*!
        \brief The plane fromXML method is used to fetch specified tags from the XML-File.

        This method fetches a specified amount of tags , the most important being:

        \list
            \i id.
            \i Two points.
            \i The color.
            \i The time.
        \endlist
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
