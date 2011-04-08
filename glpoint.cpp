#include "glpoint.h"

GLPoint::GLPoint(GLColor color, QString objectID, int time) : GLObject(color, objectID, time)
{
    _x = _y = _z = 0.0;
}

GLPoint::GLPoint( GLdouble x, GLdouble y, GLdouble z, GLColor color, QString objectID, int time ) : GLObject(color, objectID, time)
{
    _x = x;
    _y = y;
    _z = z;
}

void GLPoint::draw()
{
    glPushMatrix();

    glTranslatef( _x, _y, _z );

    glBegin (GL_LINES);

    glColor3f (_color.redF(), _color.greenF(), _color.blueF());
    glVertex3f(  0.1,  0.1,  0.0 );
    glVertex3f( -0.1, -0.1,  0.0 );

    glVertex3f( -0.1,  0.1,  0.0 );
    glVertex3f(  0.1, -0.1,  0.0 );

    glVertex3f(  0.0,  0.1,  0.1 );
    glVertex3f(  0.0, -0.1, -0.1 );

    glVertex3f(  0.0, -0.1,  0.1 );
    glVertex3f(  0.0,  0.1, -0.1 );

    glEnd ();

    glPopMatrix();
}
