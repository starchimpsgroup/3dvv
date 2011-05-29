/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "glangle.h"
#include "gltext.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define LEN 0.2

GLAngle::GLAngle( GLVector * vectorA, GLVector * vectorB, GLColor color, QString objectID, int time ) : GLObject(GLObject::ANGLE_OBJECT, color, objectID, time)
{
    if(   vectorA       != 0             &&
          vectorB       != 0             &&
          vectorA       != vectorB       &&
       ( (vectorA->sX() == vectorB->sX() && vectorA->sY() == vectorB->sY() && vectorA->sZ() == vectorB->sZ()) ||
         (vectorA->eX() == vectorB->eX() && vectorA->eY() == vectorB->eY() && vectorA->eZ() == vectorB->eZ()) ||
         (vectorA->eX() == vectorB->sX() && vectorA->eY() == vectorB->sY() && vectorA->eZ() == vectorB->sZ()) ||
         (vectorA->sX() == vectorB->eX() && vectorA->sY() == vectorB->eY() && vectorA->sZ() == vectorB->eZ()) ))
    {
        _valid = true;

        if(vectorA->eX() == vectorB->sX() && vectorA->eY() == vectorB->sY() && vectorA->eZ() == vectorB->sZ())
        {
            _vectorA = GLVector(vectorA->eX(),vectorA->eY(),vectorA->eZ(),vectorA->sX(),vectorA->sY(),vectorA->sZ());
            _vectorB = GLVector(*vectorB);
        }
        else if(vectorA->eX() == vectorB->eX() && vectorA->eY() == vectorB->eY() && vectorA->eZ() == vectorB->eZ())
        {
            _vectorA = GLVector(vectorA->eX(),vectorA->eY(),vectorA->eZ(),vectorA->sX(),vectorA->sY(),vectorA->sZ());
            _vectorB = GLVector(vectorB->eX(),vectorB->eY(),vectorB->eZ(),vectorB->sX(),vectorB->sY(),vectorB->sZ());
        }
        else if(vectorA->sX() == vectorB->eX() && vectorA->sY() == vectorB->eY() && vectorA->sZ() == vectorB->eZ())
        {
            _vectorA = GLVector(*vectorA);
            _vectorB = GLVector(vectorB->eX(),vectorB->eY(),vectorB->eZ(),vectorB->sX(),vectorB->sY(),vectorB->sZ());
        }
        else
        {
            _vectorA = GLVector(*vectorA);
            _vectorB = GLVector(*vectorB);
        }

        _vectorLeft  = GLVector(_vectorA.x() * LEN,_vectorA.y() * LEN,_vectorA.z() * LEN);
        _vectorRight = GLVector(_vectorB.x() * LEN,_vectorB.y() * LEN,_vectorB.z() * LEN);

        if(_vectorLeft.length() > _vectorRight.length())
        {
            double h = _vectorLeft.length()/_vectorRight.length();
            _vectorLeft = _vectorLeft / h;
        }
        else if(_vectorLeft.length() < _vectorRight.length())
        {
            double h = _vectorRight.length()/_vectorLeft.length();
            _vectorRight = _vectorRight / h;
        }

        _vectorMid = ((_vectorLeft  + _vectorRight)/2.0)*1.1;
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

        glTranslatef(_vectorA.sX(), _vectorA.sY(), _vectorA.sZ());

        glEnable(GL_BLEND);

        GLVector midLeft  = ((_vectorLeft  + _vectorMid)  /2.0)*1.03;
        GLVector midRight = ((_vectorRight + _vectorMid)  /2.0)*1.03;

        glColor4f (usedColor().redF(), usedColor().greenF(), usedColor().blueF(), _color.alphaF());

        glBegin(GL_POLYGON);

        glVertex3f(0.0,0.0,0.0);

        glVertex3f(_vectorLeft.x(),_vectorLeft.y(),_vectorLeft.z());

        glVertex3f(midLeft.x(),midLeft.y(),midLeft.z());

        glVertex3f(_vectorMid.x(),_vectorMid.y(),_vectorMid.z());

        glVertex3f(midRight.x(),midRight.y(),midRight.z());

        glVertex3f(_vectorRight.x(),_vectorRight.y(),_vectorRight.z());

        glVertex3f(0.0,0.0,0.0);

        glEnd();

        glBegin(GL_POLYGON);

        glVertex3f(0.0,0.0,0.0);

        glVertex3f(_vectorRight.x(),_vectorRight.y(),_vectorRight.z());

        glVertex3f(midRight.x(),midRight.y(),midRight.z());

        glVertex3f(_vectorMid.x(),_vectorMid.y(),_vectorMid.z());

        glVertex3f(midLeft.x(),midLeft.y(),midLeft.z());

        glVertex3f(_vectorLeft.x(),_vectorLeft.y(),_vectorLeft.z());

        glVertex3f(0.0,0.0,0.0);

        glEnd();

        glDisable(GL_BLEND);

        glPopMatrix();
    }
}

void GLAngle::glObjectId()
{
    if(_valid)
    {
        glPushMatrix();

        glTranslatef( _vectorA.sX()+_vectorMid.x(), _vectorA.sY()+_vectorMid.y(), _vectorA.sZ()+_vectorMid.z() );

        GLText::draw(_objectID,
                     usedColor(),
                     GLVector(0.0, GLText::heightOfText(_objectID)/2.0 + 0.15, 0.0));

        glPopMatrix();
    }
}

void GLAngle::glCoordinate()
{
    if(_valid)
    {
        glPushMatrix();

        glTranslatef( _vectorA.sX()+_vectorMid.x(), _vectorA.sY()+_vectorMid.y(), _vectorA.sZ()+_vectorMid.z() );

        GLText::draw( QString::number(_vectorA.angle(_vectorB),'d',2) + '°',
                     usedColor(),
                     GLVector(0.0, -0.35, 0.0));

        glPopMatrix();
    }
}

GLAngle * GLAngle::fromXml(const QDomElement &object, QList<GLObject*> &objects)
{
    if (object.isNull() || object.attribute("type","") != "angle")
        return NULL;

    QString id = object.attribute("id","");

    GLVector * vectorA = 0;
    GLVector * vectorB = 0;

    QDomNodeList angleObjects = object.elementsByTagName("object");
    if (angleObjects.count() == 2)
    {
        QDomElement objNode = angleObjects.at(0).toElement();
        QString id = objNode.attribute("id","");

        foreach(GLObject * o, objects)
        {
            if(o->id() == id && o->type() == GLObject::VECTOR_OBJECT)
            {
                vectorA = (GLVector *)o;
                break;
            }
        }

        objNode = angleObjects.at(1).toElement();
        id = objNode.attribute("id","");

        foreach(GLObject * o, objects)
        {
            if(o->id() == id && o->type() == GLObject::VECTOR_OBJECT)
            {
                vectorB = (GLVector *)o;
                break;
            }
        }
    }

    uchar r=0,g=0,b=0,a=255;

    QDomNodeList colors = object.elementsByTagName("color");
    if (!colors.isEmpty())
    {
        QDomElement colorNode = colors.at(0).toElement();
        r = (uchar)colorNode.attribute("r","0").toUShort(NULL, 16);
        g = (uchar)colorNode.attribute("g","0").toUShort(NULL, 16);
        b = (uchar)colorNode.attribute("b","0").toUShort(NULL, 16);
        a = (uchar)colorNode.attribute("a","64").toUShort(NULL, 16);
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
