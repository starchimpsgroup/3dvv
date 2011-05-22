#ifndef GLANGLE_H
#define GLANGLE_H

#include "globject.h"
#include "glvector.h"

class GLAngle : public GLObject
{
public:
    GLAngle( GLVector * vectorA, GLVector * vectorB, GLColor color, QString objectID, int time );

    GLVector * vectorA(){ return _vectorA; }
    GLVector * vectorB(){ return _vectorB; }

    static GLAngle * fromXml(const QDomElement &object, QList<GLObject*> &objects);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();

private:
    GLVector * _vectorA;
    GLVector * _vectorB;

    bool _valid;
};

#endif // GLANGLE_H
