#include "glline.h"
#include "gltext.h"

#define MULT 10

GLLine::GLLine( GLVector point, GLVector direction, GLColor color, QString objectID, int time ) : GLObject(GLObject::LINE_OBJECT, color, objectID, time)
{
    _line = GLVector(point.x(),point.y(),point.z(),direction.x(),direction.y(),direction.z());
}

void GLLine::glObject()
{
    glPushMatrix();

    GLVector line = GLVector(_line.eX(),_line.eY(),_line.eZ(),_line.sX(),_line.sY(),_line.sZ());

    glTranslatef(_line.sX() + _line.x()/2.0,
                 _line.sY() + _line.y()/2.0,
                 _line.sZ() + _line.z()/2.0);

    glBegin(GL_LINES);

    glColor3f (usedColor().redF(), usedColor().greenF(), usedColor().blueF());
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(_line.x() * MULT, _line.y() * MULT, _line.z() * MULT);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(line.x() * MULT, line.y() * MULT, line.z() * MULT);

    glEnd();

    glPopMatrix();
}

void GLLine::glObjectId()
{
    glPushMatrix();

    glTranslatef(_line.sX(), _line.sY(), _line.sZ());

    GLText::draw(_objectID,
                 usedColor(),
                 GLVector(_line.x()/2.0, _line.y()/2.0 + GLText::heightOfText(_objectID)/2.0 + 0.15, _line.z()/2.0));

    glPopMatrix();
}

void GLLine::glCoordinate()
{
    glPushMatrix();

    glTranslatef(_line.sX(), _line.sY(), _line.sZ());

    GLText::draw("(" + QString::number(_line.sX()) + ", " + QString::number(_line.sY()) + ", " + QString::number(_line.sZ()) + ")",
                 usedColor(),
                 GLVector(0.0, -0.35, 0.0));

    GLText::draw("(" + QString::number(_line.eX()) + ", " + QString::number(_line.eY()) + ", " + QString::number(_line.eZ()) + ")",
                 usedColor(),
                 GLVector(_line.x(), _line.y()-0.35, _line.z()));

    glPopMatrix();
}

void GLLine::glVector()
{
    glPushMatrix();

    glTranslatef(_line.sX(), _line.sY(), _line.sZ());

    QString vector = QString::number(_line.x()) + "\n" + QString::number(_line.y()) + "\n" + QString::number(_line.z());
    GLText::draw("(" + vector + ")",
                 usedColor(),
                 GLVector(_line.x()/2.0, _line.y()/2.0 - GLText::heightOfText(vector)/2.0 - 0.15, _line.z()/2.0));

    glPopMatrix();
}
