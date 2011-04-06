#ifndef GLPOINT_H
#define GLPOINT_H

#include "qgl.h"
#include "globject.h"

class GLPoint : public GLObject
{
public:
    void draw();

    GLPoint(){ _x = _y = _z = 0.0; }
    GLPoint( GLdouble x, GLdouble y, GLdouble z ){ _x = x;
                                                   _y = y;
                                                   _z = z; }

private:
    GLdouble _x;
    GLdouble _z;
    GLdouble _y;
};

#endif // GLPOINT_H
