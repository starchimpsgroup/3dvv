#ifndef GLPLAIN_H
#define GLPLAIN_H

#include "globject.h"
#include "glvector.h"

class GLPlain : public GLObject
{
public:
    GLPlain(GLVector point, GLVector normal, GLColor color, QString objectID, int time);

    void draw();

    void drawObjectId();
    void drawCoordinate();

private:
    GLVector _normal;
    GLVector _point;
};

#endif // GLPLAIN_H
