/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "glvector.h"
#include "math.h"
#include <qgl.h>
#include "gltext.h"

//#define TEST

GLVector::GLVector(GLColor color, QString objectID, int time) : GLObject(color, objectID, time)
{
    _sX = _sY = _sZ =
    _eX = _eY = _eZ = 0.0;
}

GLVector::GLVector(GLdouble x, GLdouble y, GLdouble z, GLColor color, QString objectID, int time) : GLObject(color, objectID, time)
{
    _sX =    _sY =    _sZ = 0.0;
    _eX = x; _eY = y; _eZ = z;
}

GLVector::GLVector(GLdouble sX, GLdouble sY, GLdouble sZ, GLdouble eX, GLdouble eY, GLdouble eZ, GLColor color, QString objectID, int time) : GLObject(color, objectID, time)
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

void GLVector::draw()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    glBegin (GL_LINES);
    glColor3f (_color.redF(), _color.greenF(), _color.blueF());
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(x(), y(), z());
    glEnd ();

#ifdef TEST
        glBegin (GL_LINES);

        glColor3f (0.0, 0.0, 0.0);
        glVertex3f(x(), 0.0, 0.0);
        glVertex3f(x(), y(), z());

        glColor3f (0.0, 0.0, 0.0);
        glVertex3f(0.0, y(), 0.0);
        glVertex3f(x(), y(), z());

        glColor3f (0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, z());
        glVertex3f(x(), y(), z());

        glColor3f (0.0, 0.0, 0.0);
        glVertex3f(x(), 0.0, 0.0);
        glVertex3f(x() * len, y() * len, z() * len);

        glColor3f (0.0, 0.0, 0.0);
        glVertex3f(0.0, y(), 0.0);
        glVertex3f(x() * len, y() * len, z() * len);

        glColor3f (0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, z());
        glVertex3f(x() * len, y() * len, z() * len);

        glEnd ();
#endif

    /**
      * Spitze
      */

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

    glColor3f (_color.redF(), _color.greenF(), _color.blueF());
    gluCylinder(gluNewQuadric(), 0.1, 0, 0.3, 16, 4);

    glRotatef(180, 1.0, 0.0, 0.0);
    gluDisk(gluNewQuadric(), 0, 0.1, 16, 4);

    glPopMatrix();
}

void GLVector::drawObjectId()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    GLText::draw(_objectID,
                 _color,
                 GLVector(x()/2.0, y()/2.0 + GLText::heightOfText(_objectID)/2.0 + 0.15, z()/2.0));

    glPopMatrix();
}

void GLVector::drawCoordinate()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    GLText::draw("(" + QString::number(_sX) + ", " + QString::number(_sY) + ", " + QString::number(_sZ) + ")",
                 _color,
                 GLVector(0.0, -0.35, 0.0));

    GLText::draw("(" + QString::number(_eX) + ", " + QString::number(_eY) + ", " + QString::number(_eZ) + ")",
                 _color,
                 GLVector(x(), y()-0.35, z()));

    glPopMatrix();
}

void GLVector::drawVector()
{
    glPushMatrix();

    glTranslatef(_sX, _sY, _sZ);

    QString vector = QString::number(x()) + "\n" + QString::number(y()) + "\n" + QString::number(z());
    GLText::draw("(" + vector + ")",
                 _color,
                 GLVector(x()/2.0, y()/2.0 - GLText::heightOfText(vector)/2.0 - 0.15, z()/2.0));

    glPopMatrix();
}
