#include <QString>
#include "glcolor.h"

#ifndef GLOBJECT_H
#define GLOBJECT_H

class GLObject
{
public:
    GLObject();
    virtual void draw() = 0;

private:
    QString objectID;
    GLColor color;
};

#endif // GLOBJECT_H
