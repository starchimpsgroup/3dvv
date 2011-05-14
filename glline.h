#ifndef GLLINE_H
#define GLLINE_H

#include "globject.h"

class GLLine : public GLObject
{
public:
    GLLine( GLColor color, QString objectID, int time );
};

#endif // GLLINE_H
