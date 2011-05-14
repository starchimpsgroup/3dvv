#include "glplain.h"
#include "gltext.h"

#define MULT 3

GLPlain::GLPlain(GLVector point, GLVector normal, GLColor color, QString objectID, int time) : GLObject(GLObject::PLAIN, color, objectID, time)
{
    _point  = point;
    _normal = normal;
}

void GLPlain::glObject()
{
    glPushMatrix();

    glTranslatef(_point.x(), _point.y(), _point.z());

    GLdouble angleX = v_Y.angle(_normal) - 90.0;
    GLdouble angleY = v_Z.angle(GLVector(_normal.x(), 0.0, _normal.z()));

    if(_normal.x() < 0)
        angleY *= -1;

    //_normal.draw();

    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);

    glColor4f (_color.redF(), _color.greenF(), _color.blueF(), _color.alphaF());

    glEnable(GL_BLEND);

    glBegin( GL_QUADS );
    glVertex2d(-0.5 * MULT,-0.5 * MULT);
    glVertex2d( 0.5 * MULT,-0.5 * MULT);
    glVertex2d( 0.5 * MULT, 0.5 * MULT);
    glVertex2d(-0.5 * MULT, 0.5 * MULT);
    glEnd();

    glRotatef(180, 1.0, 0.0, 0.0);

    glBegin( GL_QUADS );
    glVertex2d(-0.5 * MULT,-0.5 * MULT);
    glVertex2d( 0.5 * MULT,-0.5 * MULT);
    glVertex2d( 0.5 * MULT, 0.5 * MULT);
    glVertex2d(-0.5 * MULT, 0.5 * MULT);
    glEnd();

    glDisable(GL_BLEND);

    glPopMatrix();
}

void GLPlain::glObjectId()
{
    glPushMatrix();

    glTranslatef( _point.x(), _point.y(), _point.z() );

    GLText::draw(_objectID,
                 _color,
                 GLVector(0.0, GLText::heightOfText(_objectID)/2.0 + 0.15, 0.0));

    glPopMatrix();
}

void GLPlain::glCoordinate()
{
    glPushMatrix();

    glTranslatef( _point.x(), _point.y(), _point.z() );

    GLText::draw("(" + QString::number(_point.x()) + ", " + QString::number(_point.y()) + ", " + QString::number(_point.z()) + ")",
                 _color,
                 GLVector(0.0, -0.35, 0.0));

    glPopMatrix();
}
