/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "glplane.h"
#include "gltext.h"

#define MULT 300

GLPlane::GLPlane(GLVector point, GLVector normal, GLColor color, QString objectID, int time) : GLObject(GLObject::PLANE_OBJECT, color, objectID, time)
{
    _point  = point;
    _normal = normal;
}

void GLPlane::glObject()
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

    glColor4f (usedColor().redF(), usedColor().greenF(), usedColor().blueF(), _color.alphaF());

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

void GLPlane::glObjectId()
{
    glPushMatrix();

    glTranslatef( _point.x(), _point.y(), _point.z() );

    GLText::draw(_objectID,
                 usedColor(),
                 GLVector(0.0, GLText::heightOfText(_objectID)/2.0 + 0.15, 0.0));

    glPopMatrix();
}

void GLPlane::glCoordinate()
{
    glPushMatrix();

    glTranslatef( _point.x(), _point.y(), _point.z() );

    GLText::draw("(" + QString::number(_point.x()) + ", " + QString::number(_point.y()) + ", " + QString::number(_point.z()) + ")",
                 usedColor(),
                 GLVector(0.0, -0.35, 0.0));

    glPopMatrix();
}

GLPlane * GLPlane::fromXml(const QDomElement &object)
{
    if (object.isNull() || object.attribute("type","") != "plane")
        return NULL;

    QString id = object.attribute("id","");

    GLVector pointVec;
    GLVector normalVec;

    QDomNodeList points = object.elementsByTagName("point");
    if (!points.isEmpty())
    {
        QDomElement point = points.at(0).toElement();
        pointVec = GLVector(point.attribute("x","0").toDouble(),
                            point.attribute("y","0").toDouble(),
                            point.attribute("z","0").toDouble());
    }

    QDomNodeList normals = object.elementsByTagName("normal");
    if (!normals.isEmpty())
    {
        QDomElement normal = normals.at(0).toElement();
        normalVec = GLVector(normal.attribute("x","0").toDouble(),
                             normal.attribute("y","0").toDouble(),
                             normal.attribute("z","0").toDouble());
    }

    uchar r=0,g=0,b=0,a=125;

    QDomNodeList colors = object.elementsByTagName("color");
    if (!colors.isEmpty())
    {
        QDomElement colorNode = colors.at(0).toElement();
        r = (uchar)colorNode.attribute("r","0").toUShort(NULL, 16);
        g = (uchar)colorNode.attribute("g","0").toUShort(NULL, 16);
        b = (uchar)colorNode.attribute("b","0").toUShort(NULL, 16);
        a = (uchar)colorNode.attribute("a","7d").toUShort(NULL, 16);
    }

    int time = 0;
    QDomNodeList times = object.elementsByTagName("time");
    if (!times.isEmpty())
    {
        QDomElement timeNode = times.at(0).toElement();
        time = timeNode.text().toInt();
    }

    return new GLPlane(pointVec,normalVec,GLColor(r,g,b,a),id,time);
}
