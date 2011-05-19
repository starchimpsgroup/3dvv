#include "glangle.h"
#include "gltext.h"

#define _USE_MATH_DEFINES
#include <cmath>

GLAngle::GLAngle( GLVector * vectorA, GLVector * vectorB, GLColor color, QString objectID, int time ) : GLObject(GLObject::ANGLE_OBJECT, color, objectID, time)
{
    _vectorA = vectorA;
    _vectorB = vectorB;

    if(_vectorA       != 0              &&
       _vectorB       != 0              &&
       _vectorA       != _vectorB       &&
       _vectorA->sX() == _vectorB->sX() &&
       _vectorA->sY() == _vectorB->sY() &&
       _vectorA->sZ() == _vectorB->sZ() )
    {
        _valid = true;
    }
    else
    {
        _valid = false;
    }
}

void GLAngle::glObject()
{
    if(_valid)
    {
        glPushMatrix();

        glTranslatef(_vectorA->sX(), _vectorA->sY(), _vectorA->sZ());

        /*GLText::draw(_objectID,
                     _color,
                     GLVector(_line.x()/2.0, _line.y()/2.0 + GLText::heightOfText(_objectID)/2.0 + 0.15, _line.z()/2.0));*/

        GLVector vectorZ;

        if(_vectorA->eZ() < _vectorB->eZ())
        {
            vectorZ = GLVector(0.0, _vectorA->eY(),_vectorA->eZ(),0.0, _vectorB->eY(),_vectorB->eZ());
        }
        else
        {
            vectorZ = GLVector(0.0, _vectorB->eY(),_vectorB->eZ(),0.0, _vectorA->eY(),_vectorA->eZ());
        }

        double angle  = _vectorA->angle(*_vectorB);
        double angleX = v_Y.angle(vectorZ);
        double angleZ = v_X.angle(*_vectorA + *_vectorB) - angle/2.0;

        //qDebug("angel: %f", angleZ);

        //
        glRotatef(angleX, 1.0, 0.0, 0.0);glRotatef(angleZ, 0.0, 0.0, 1.0);

        glBegin(GL_LINE_STRIP);
        glColor3f (_color.redF(), _color.greenF(), _color.blueF());

        float f = 0.0;
        for(int i = 0; i <= angle; i++)
        {
            glVertex3f(cos(f),sin(f),0);
            f += (2*M_PI/360);
        }
        glEnd();

        glPopMatrix();
    }
}

GLAngle * GLAngle::fromXml(const QDomElement &object, QList<GLObject*> &objects)
{
    if (object.isNull() || object.attribute("type") != "angle")
        return NULL;

    QString id = object.attribute("id");

    GLVector * vectorA = 0;
    GLVector * vectorB = 0;

    QDomNodeList angleObjects = object.elementsByTagName("object");
    if (angleObjects.count() == 2)
    {
        QDomElement objNode = angleObjects.at(0).toElement();
        QString id = objNode.attribute("id");

        foreach(GLObject * o, objects)
        {
            if(o->id() == id && o->type() == GLObject::VECTOR_OBJECT)
            {
                vectorA = (GLVector *)o;
                break;
            }
        }

        objNode = angleObjects.at(1).toElement();
        id = objNode.attribute("id");

        foreach(GLObject * o, objects)
        {
            if(o->id() == id && o->type() == GLObject::VECTOR_OBJECT)
            {
                vectorB = (GLVector *)o;
                break;
            }
        }
    }

    uchar r,g,b,a;

    QDomNodeList colors = object.elementsByTagName("color");
    if (!colors.isEmpty())
    {
        QDomElement colorNode = colors.at(0).toElement();
        r = (uchar)colorNode.attribute("r").toUShort(NULL, 16);
        g = (uchar)colorNode.attribute("g").toUShort(NULL, 16);
        b = (uchar)colorNode.attribute("b").toUShort(NULL, 16);
        a = (uchar)colorNode.attribute("a").toUShort(NULL, 16);
    }

    int time = 0;
    QDomNodeList times = object.elementsByTagName("time");
    if (!times.isEmpty())
    {
        QDomElement timeNode = times.at(0).toElement();
        time = timeNode.text().toInt();
    }

    return new GLAngle(vectorA,vectorB,GLColor(r,g,b,a),id,time);
}
