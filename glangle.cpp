#include "glangle.h"
#include "gltext.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define LEN 0.2
#define PARTS 20.0

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

        glEnable(GL_BLEND);

        GLVector left(_vectorA->x() * LEN,_vectorA->y() * LEN,_vectorA->z() * LEN);
        GLVector right(_vectorB->x() * LEN,_vectorB->y() * LEN,_vectorB->z() * LEN);

        if(left.length() > right.length())
        {
            double h = left.length()/right.length();
            left = left / h;
        }
        else if(left.length() < right.length())
        {
            double h = right.length()/left.length();
            right = right / h;
        }

        GLVector mid      = ((left  + right)/2.0)*1.1;
        GLVector midLeft  = ((left  + mid)  /2.0)*1.03;
        GLVector midRight = ((right + mid)  /2.0)*1.03;

        glColor4f (usedColor().redF(), usedColor().greenF(), usedColor().blueF(), _color.alphaF());

        glBegin(GL_POLYGON);

        glVertex3f(0.0,0.0,0.0);

        glVertex3f(left.x(),left.y(),left.z());

        glVertex3f(midLeft.x(),midLeft.y(),midLeft.z());

        glVertex3f(mid.x(),mid.y(),mid.z());

        glVertex3f(midRight.x(),midRight.y(),midRight.z());

        glVertex3f(right.x(),right.y(),right.z());

        glVertex3f(0.0,0.0,0.0);

        glEnd();

        glBegin(GL_POLYGON);

        glVertex3f(0.0,0.0,0.0);

        glVertex3f(right.x(),right.y(),right.z());

        glVertex3f(midRight.x(),midRight.y(),midRight.z());

        glVertex3f(mid.x(),mid.y(),mid.z());

        glVertex3f(midLeft.x(),midLeft.y(),midLeft.z());

        glVertex3f(left.x(),left.y(),left.z());

        glVertex3f(0.0,0.0,0.0);

        glEnd();

        glDisable(GL_BLEND);

        // #####

        //glTranslatef(_vectorA->sX(), _vectorA->sY(), _vectorA->sZ());

        /*GLText::draw(_objectID,
                     _color,
                     GLVector(_line.x()/2.0, _line.y()/2.0 + GLText::heightOfText(_objectID)/2.0 + 0.15, _line.z()/2.0));*/

        /*double angle  = _vectorA->angle(*_vectorB)+1;
        double angleY = v_X.angle(GLVector(_vectorA->x(),0.0,_vectorA->z()));

        if(_vectorA->y() < 0.0)
            angleY *= -1;

        //double angleZ = v_X.angle(GLVector(_vectorA->x(),_vectorA->y(),0.0));
        double angleZ = _vectorA->angle(GLVector(_vectorA->x(),0.0,_vectorA->z()));

        if(_vectorA->y() < 0.0)
           angleZ *= -1;

        //GLVector end(_vectorA->eX(),_vectorA->eY(),_vectorA->eZ(),_vectorB->eX(),_vectorB->eY(),_vectorB->eZ());

        //double angleX = end.angle(GLVector(end.x(),0.0,end.z())) + 90.0;
        double angleX = 90.0;

        //angleX = 360 - angleX;
        //angleX *= -1;

        glRotatef(angleY, 0.0, 1.0, 0.0);
        glRotatef(angleZ, 0.0, 0.0, 1.0);
        //glRotatef(angleX, 1.0, 0.0, 0.0);

        glBegin (GL_LINES);

        glVertex3f (0,0,0);
        glVertex3f (1,0,0);

        glVertex3f (0,0,0);
        glVertex3f (0,1,0);

        glVertex3f (0,0,0);
        glVertex3f (0,0,1);

        glEnd ();

        glEnable(GL_BLEND);

        glBegin(GL_LINE_STRIP);
        glColor4f (usedColor().redF(), usedColor().greenF(), usedColor().blueF(), _color.alphaF());

        float f = 0.0;
        for(int i = 0; i <= angle; i++)
        {
            glVertex3f(cos(f),sin(f),0);
            f += (2*M_PI/360);
        }
        glEnd();

        glDisable(GL_BLEND);*/

        glPopMatrix();
    }
}

void GLAngle::glObjectId()
{
    if(_valid)
    {
        glPushMatrix();

        glTranslatef( _vectorA->sX(), _vectorA->sY(), _vectorA->sZ() );
        GLVector mid = (*_vectorA + *_vectorB) * LEN/2.0;
        glTranslated( mid.x(), mid.y(), mid.z() );

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

        glTranslatef( _vectorA->sX(), _vectorA->sY(), _vectorA->sZ() );
        GLVector mid = (*_vectorA + *_vectorB) * LEN/2.0;
        glTranslated( mid.x(), mid.y(), mid.z() );

        GLText::draw( QString::number(_vectorA->angle(*_vectorB)),
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
        a = (uchar)colorNode.attribute("a","d7").toUShort(NULL, 16);
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
