#include "glpoint.h"
#include "gltext.h"

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

void GLPoint::drawObjectId()
{
    glPushMatrix();

    glTranslatef( _x, _y, _z );

    GLText::draw(_objectID,
                 _color,
                 GLVector(0.0, GLText::heightOfText(_objectID)/2.0 + 0.15, 0.0));

    glPopMatrix();
}

void GLPoint::drawCoordinate()
{
    glPushMatrix();

    glTranslatef( _x, _y, _z );

    GLText::draw("(" + QString::number(_x) + ", " + QString::number(_y) + ", " + QString::number(_z) + ")",
                 _color,
                 GLVector(0.0, -0.35, 0.0));

    glPopMatrix();
}
