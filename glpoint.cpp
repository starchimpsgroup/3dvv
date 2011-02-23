#include "glpoint.h"

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
