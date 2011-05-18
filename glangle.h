#ifndef GLANGLE_H
#define GLANGLE_H

#include "globject.h"
#include "glvector.h"

class GLAngle : public GLObject
{
public:
    GLAngle( GLVector * vectorA, GLVector * vectorB, GLColor color, QString objectID, int time );

protected:
    void glObject();

private:
    GLVector * _vectorA;
    GLVector * _vectorB;

    bool _valid;
};

#endif // GLANGLE_H
