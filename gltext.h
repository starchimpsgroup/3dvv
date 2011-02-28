#ifndef GLTEXT_H
#define GLTEXT_H

#include <QString>
#include "glcolor.h"
#include "glvector.h"
#include <qgl.h>

#define TEXTSIZE 100
#define PIXEL 1/256

class GLText
{
public:
    static void draw( QString text, GLColor color, GLVector position, GLfloat angleY, GLfloat angleX );
};

#endif // GLTEXT_H
