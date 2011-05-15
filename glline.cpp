#include "glline.h"
#include "gltext.h"

GLLine::GLLine( GLVector point, GLVector direction, GLColor color, QString objectID, int time ) : GLObject(GLObject::LINE, color, objectID, time)
{
    _point     = point;
    _direction = direction;
}

void GLLine::glObject()
{
    glBegin(GL_LINES);

    glColor3f (_color.redF(), _color.greenF(), _color.blueF());
    glVertex3f(_point.x(), _point.y(), _point.z());
    glVertex3f(_direction.x(), _direction.y(), _direction.z());

    glEnd();
}

void GLLine::glObjectId()
{
    GLVector mid(_point.x(), _point.y(), _point.z(), _direction.x(), _direction.y(), _direction.z());

    glPushMatrix();

    glTranslatef(_point.x(), _point.y(), _point.z());

    GLText::draw(_objectID,
                 _color,
                 GLVector(mid.x()/2.0, mid.y()/2.0 + GLText::heightOfText(_objectID)/2.0 + 0.15, mid.z()/2.0));

    glPopMatrix();
}

void GLLine::glCoordinate()
{
    GLText::draw("(" + QString::number(_point.x()) + ", " + QString::number(_point.y()) + ", " + QString::number(_point.z()) + ")",
                 _color,
                 GLVector(_point.x(), _point.y()-0.35, _point.z()));

    GLText::draw("(" + QString::number(_direction.x()) + ", " + QString::number(_direction.y()) + ", " + QString::number(_direction.z()) + ")",
                 _color,
                 GLVector(_direction.x(), _direction.y()-0.35, _direction.z()));
}

void GLLine::glVector()
{
    GLVector mid(_point.x(), _point.y(), _point.z(), _direction.x(), _direction.y(), _direction.z());

    glPushMatrix();

    glTranslatef(_point.x(), _point.y(), _point.z());

    QString vector = QString::number(mid.x()) + "\n" + QString::number(mid.y()) + "\n" + QString::number(mid.z());
    GLText::draw("(" + vector + ")",
                 _color,
                 GLVector(mid.x()/2.0, mid.y()/2.0 - GLText::heightOfText(vector)/2.0 - 0.15, mid.z()/2.0));

    glPopMatrix();
}
