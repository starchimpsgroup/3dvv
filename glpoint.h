#ifndef GLPOINT_H
#define GLPOINT_H

#include "qgl.h"
#include "globject.h"

class GLPoint : public GLObject
{
public:
    GLPoint( GLColor color = GLColor(), QString objectID = "", int time = 0 );
    GLPoint( GLdouble x, GLdouble y, GLdouble z, GLColor color = GLColor(), QString objectID = "", int time = 0 );

    void draw();

    void drawObjectId();
    void drawCoordinate();
    void drawVector(){};

private:
    GLdouble _x;
    GLdouble _z;
    GLdouble _y;
};

#endif // GLPOINT_H
