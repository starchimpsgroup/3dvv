#ifndef GLLINE_H
#define GLLINE_H

#include "globject.h"
#include "glvector.h"

class GLLine : public GLObject
{
public:
    GLLine( GLVector point, GLVector direction, GLColor color, QString objectID, int time );

    GLVector line(){ return _line; }

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();
    void glVector();

private:
    GLVector _line;
};

#endif // GLLINE_H
