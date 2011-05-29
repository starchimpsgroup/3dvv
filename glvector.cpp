/***************************************************************************
 *   Copyright (C) 2007 by Walter Roth                                     *
 *   info@fh-swf.de                                                        *
 *                                                                         *
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "glvector.h"
#include <qgl.h>
#include "gltext.h"

#define _USE_MATH_DEFINES
#include <cmath>

//#define TEST

GLVector::GLVector(GLColor color, QString objectID, int time) : GLObject(GLObject::VECTOR_OBJECT, color, objectID, time)
{
    _sX = _sY = _sZ =
    _eX = _eY = _eZ = 0.0;
}

GLVector::GLVector(GLdouble x, GLdouble y, GLdouble z, GLColor color, QString objectID, int time) : GLObject(GLObject::VECTOR_OBJECT, color, objectID, time)
{
    _sX =    _sY =    _sZ = 0.0;
    _eX = x; _eY = y; _eZ = z;
}

GLVector::GLVector(GLdouble sX, GLdouble sY, GLdouble sZ, GLdouble eX, GLdouble eY, GLdouble eZ, GLColor color, QString objectID, int time) : GLObject(GLObject::VECTOR_OBJECT, color, objectID, time)
{
    _sX = sX; _sY = sY; _sZ = sZ;
    _eX = eX; _eY = eY; _eZ = eZ;
}

GLVector::GLVector(const GLVector &v) : GLObject(v)
{
    if(this != &v){
        _sX       = v.sX();
        _sY       = v.sY();
        _sZ       = v.sZ();
        _eX       = v.eX();
        _eY       = v.eY();
        _eZ       = v.eZ();
    }
}

GLdouble GLVector::latitude()const{
  GLdouble lengthXZ = sqrt(x() * x() + z() * z());

  GLdouble latitude;
  if (lengthXZ != 0.0)
   latitude = atan(y() / lengthXZ);
  else{
     if( y() > 0.0)
      latitude = M_PI / 2.0;
     else latitude = -M_PI / 2.0;
  }
  return latitude / M_PI * 180.0;
}

GLdouble GLVector::longitude()const{
  GLdouble longitude;
  if(z() == 0.0){
      if(x() > 0.0)
         longitude = M_PI / 2.0;
      else longitude = -M_PI / 2.0;
    }
  else longitude = atan(x() / z());
  if((z() < 0.0) & (x() > 0.0))
   longitude += M_PI;
  if((x() < 0.0) & (z() < 0.0))
   longitude -= M_PI;
  return longitude / M_PI * 180.0;
}

void GLVector::setRadiusLongitudeLatitude(GLdouble radius, GLdouble longitude, GLdouble latitude){
  GLdouble radLongitude = longitude * M_PI / 180.0; // may be more than +-180 degree
  GLdouble radLatitude = latitude * M_PI / 180.0;
  //Not more than +- 90 degree.
  if(radLatitude > M_PI / 2.0)
    radLatitude = M_PI/ 2.0;
  if(radLatitude < -M_PI / 2.0)
    radLatitude = -M_PI/ 2.0;
  setX( radius * sin(radLongitude)* cos(radLatitude) );
  setY( radius * sin(radLatitude) );
  setZ( radius * cos(radLongitude)* cos(radLatitude) );
}

const GLVector GLVector::normalVector(const GLVector& v)const{
 return vectorMult(v).unitVector();
}

const GLVector GLVector::unitVector()const{
 GLdouble aLength;
 aLength= length();
 if (length() != 0.0)
  return GLVector(x() / length(),
                  y() / length(),
                  z() / length());
  else {
   return GLVector();
  }
}

const GLVector GLVector::vectorMult( const GLVector& v)const{
 return GLVector(
   y() * v.z() - z() * v.y(),
   z() * v.x() - x() * v.z(),
   x() * v.y() - y() * v.x());
}

const GLVector GLVector::operator -(const GLVector& v)const{
    return GLVector(x() - v.x(), y() - v.y(), z() - v.z());
}

const GLVector GLVector::operator +(const GLVector& v)const{
    return GLVector(x() + v.x(), y() + v.y(), z() + v.z());
}

GLdouble GLVector::operator *(const GLVector &v )const{
    return  x() * v.x() + y() * v.y() + z() * v.z();
}

GLVector GLVector::operator *(const GLdouble d )const{
    return  GLVector(x() * d, y() * d, z() * d);
}

const GLVector GLVector::operator /(GLdouble d)const{
    if (d != 0.0){
        GLdouble temp= 1.0 / d;
        return GLVector(x() * temp, y() * temp, z() * temp);
    }
    else{
        return GLVector(0.0,0.0,0.0);
    }
}

const GLVector operator *(GLdouble d, const GLVector &v){
    return v * d;
}

GLVector GLVector::operator = (const GLVector & v){
    if(this != &v){
        _sX = v.sX();
        _sY = v.sY();
        _sZ = v.sZ();
        _eX = v.eX();
        _eY = v.eY();
        _eZ = v.eZ();
    }
    return *this;
}

bool GLVector::operator != (const GLVector &v) const{
 return ! (*this == v);
}

bool GLVector::operator == (const GLVector &v) const{
 return ((v.x() == x()) & (v.y() == y()) & (v.z() == z()));
}

GLdouble GLVector::length()const{
    return sqrt(x()*x() + y()*y() + z()*z());
}

GLdouble GLVector::angle( const GLVector &v )
{
    return acos( (*this * v) / (this->length() * v.length()) ) * 180.0 / M_PI;
}

void GLVector::glObject()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    glEnable(GL_BLEND);

    glBegin (GL_LINES);
    glColor4f (usedColor().redF(), usedColor().greenF(), usedColor().blueF(), _color.alphaF());
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(x(), y(), z());
    glEnd ();

    glDisable(GL_BLEND);

#ifdef TEST
        glBegin (GL_LINES);

        glColor3f (0.0, 0.0, 0.0);
        glVertex3f(x(), 0.0, 0.0);
        glVertex3f(x(), y(), z());

        glVertex3f(0.0, y(), 0.0);
        glVertex3f(x(), y(), z());

        glVertex3f(0.0, 0.0, z());
        glVertex3f(x(), y(), z());

        glVertex3f(x(), 0.0, 0.0);
        glVertex3f(x() * len, y() * len, z() * len);

        glVertex3f(0.0, y(), 0.0);
        glVertex3f(x() * len, y() * len, z() * len);

        glVertex3f(0.0, 0.0, z());
        glVertex3f(x() * len, y() * len, z() * len);

        glEnd ();
#endif

    // Peak

    GLdouble len = ((this->length() - 0.3) /  this->length());

    glTranslatef(x() * len, y() * len, z() * len);

    GLVector vectorXZ(this->x(), 0.0, this->z());

    GLdouble angleXZ = v_Z.angle(vectorXZ);
    GLdouble angleYZ = this->angle(vectorXZ);

    if( this->x() < 0 )
        angleXZ *= -1;

    if( this->y() > 0 )
        angleYZ *= -1;

    if( this->x() == 0 && this->z() == 0 )
    {
        if( this->y() > 0 )
        {
            angleYZ = 270;
        }
        else if( this->y() < 0 )
        {
            angleYZ = 90;
        }
    }

#ifdef TEST
        glBegin (GL_LINES);
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(vectorXZ.x(), vectorXZ.y(), vectorXZ.z());
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(v_Z.x(), v_Z.y(), v_Z.z());
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(this->x(), this->y(), this->z());
        glEnd ();
#endif

    glRotatef(angleXZ, 0.0, 1.0, 0.0);
    glRotatef(angleYZ, 1.0, 0.0, 0.0);

    glEnable(GL_BLEND);

    glColor4f (usedColor().redF(), usedColor().greenF(), usedColor().blueF(), _color.alphaF());
    gluCylinder(gluNewQuadric(), 0.1, 0, 0.3, 16, 4);

    glRotatef(180, 1.0, 0.0, 0.0);
    gluDisk(gluNewQuadric(), 0, 0.1, 16, 4);

    glDisable(GL_BLEND);

    glPopMatrix();
}

void GLVector::glObjectId()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    GLText::draw(_objectID,
                 usedColor(),
                 GLVector(x()/2.0, y()/2.0 + GLText::heightOfText(_objectID)/2.0 + 0.15, z()/2.0));

    glPopMatrix();
}

void GLVector::glCoordinate()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    GLText::draw("(" + QString::number(_sX) + ", " + QString::number(_sY) + ", " + QString::number(_sZ) + ")",
                 usedColor(),
                 GLVector(0.0, -0.35, 0.0));

    GLText::draw("(" + QString::number(_eX) + ", " + QString::number(_eY) + ", " + QString::number(_eZ) + ")",
                 usedColor(),
                 GLVector(x(), y()-0.35, z()));

    glPopMatrix();
}

void GLVector::glVector()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    QString vector = QString::number(x()) + "\n" + QString::number(y()) + "\n" + QString::number(z());
    GLText::draw("(" + vector + ")",
                 usedColor(),
                 GLVector(x()/2.0, y()/2.0 - GLText::heightOfText(vector)/2.0 - 0.15, z()/2.0));

    glPopMatrix();
}

GLVector * GLVector::fromXml(const QDomElement &object)
{

    if (object.isNull() || object.attribute("type","") != "vector")
        return NULL;

    QString id = object.attribute("id","");

    GLdouble sx = 0.0;
    GLdouble sy = 0.0;
    GLdouble sz = 0.0;

    GLdouble ex = 0.0;
    GLdouble ey = 0.0;
    GLdouble ez = 0.0;

    QDomNodeList points = object.elementsByTagName("point");
    if (points.count() == 2)
    {
        QDomElement point = points.at(0).toElement();
        sx = point.attribute("x","0").toDouble();
        sy = point.attribute("y","0").toDouble();
        sz = point.attribute("z","0").toDouble();
        point = points.at(1).toElement();
        ex = point.attribute("x","0").toDouble();
        ey = point.attribute("y","0").toDouble();
        ez = point.attribute("z","0").toDouble();
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

    return new GLVector(sx,sy,sz,ex,ey,ez,GLColor(r,g,b,a),id,time);
}
