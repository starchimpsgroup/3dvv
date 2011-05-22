#include "glpoint.h"
#include "gltext.h"

GLPoint::GLPoint( GLColor color, QString objectID, int time ) : GLObject(GLObject::POINT_OBJECT, color, objectID, time)
{
    _x = _y = _z = 0.0;
}

GLPoint::GLPoint( GLdouble x, GLdouble y, GLdouble z, GLColor color, QString objectID, int time ) : GLObject(GLObject::POINT_OBJECT, color, objectID, time)
{
    _x = x;
    _y = y;
    _z = z;
}

void GLPoint::glObject()
{
    glPushMatrix();

    glTranslatef( _x, _y, _z );

    glBegin(GL_LINES);

    glColor3f (usedColor().redF(), usedColor().greenF(), usedColor().blueF());
    glVertex3f(  0.1,  0.1,  0.0 );
    glVertex3f( -0.1, -0.1,  0.0 );

    glVertex3f( -0.1,  0.1,  0.0 );
    glVertex3f(  0.1, -0.1,  0.0 );

    glVertex3f(  0.0,  0.1,  0.1 );
    glVertex3f(  0.0, -0.1, -0.1 );

    glVertex3f(  0.0, -0.1,  0.1 );
    glVertex3f(  0.0,  0.1, -0.1 );

    glEnd();

    glPopMatrix();
}

void GLPoint::glObjectId()
{
    glPushMatrix();

    glTranslatef( _x, _y, _z );

    GLText::draw(_objectID,
                 usedColor(),
                 GLVector(0.0, GLText::heightOfText(_objectID)/2.0 + 0.15, 0.0));

    glPopMatrix();
}

void GLPoint::glCoordinate()
{
    glPushMatrix();

    glTranslatef( _x, _y, _z );

    GLText::draw("(" + QString::number(_x) + ", " + QString::number(_y) + ", " + QString::number(_z) + ")",
                 usedColor(),
                 GLVector(0.0, -0.35, 0.0));

    glPopMatrix();
}

GLPoint * GLPoint::fromXml(const QDomElement &object)
{
    if (object.isNull() || object.attribute("type","") != "point")
        return NULL;

    QString id = object.attribute("id","");

    GLdouble x = 0.0;
    GLdouble y = 0.0;
    GLdouble z = 0.0;

    QDomNodeList points = object.elementsByTagName("point");
    if (!points.isEmpty())
    {
        QDomElement point = points.at(0).toElement();
        x = point.attribute("x","0").toDouble();
        y = point.attribute("y","0").toDouble();
        z = point.attribute("z","0").toDouble();
    }

    uchar r=0,g=0,b=0,a=255;

    QDomNodeList colors = object.elementsByTagName("color");
    if (!colors.isEmpty())
    {
        QDomElement colorNode = colors.at(0).toElement();
        r = (uchar)colorNode.attribute("r","0").toUShort(NULL, 16);
        g = (uchar)colorNode.attribute("g","0").toUShort(NULL, 16);
        b = (uchar)colorNode.attribute("b","0").toUShort(NULL, 16);
        a = (uchar)colorNode.attribute("a","ff").toUShort(NULL, 16);
    }

    int time = 0;
    QDomNodeList times = object.elementsByTagName("time");
    if (!times.isEmpty())
    {
        QDomElement timeNode = times.at(0).toElement();
        time = timeNode.text().toInt();
    }

    return new GLPoint(x,y,z, GLColor(r,g,b,a), id, time);
}
