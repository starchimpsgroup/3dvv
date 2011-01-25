/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst                                 *
 *   christian@ernst-menden.de                                             *
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

GLVector::GLVector(const GLVector &v){
    if(this != &v){
        _x = v.x();
        _y = v.y();
        _z = v.z();
    }
}

GLdouble GLVector::latitude()const{
  GLdouble lengthXZ = sqrt(_x * _x + _z * _z);

  GLdouble latitude;
  if (lengthXZ != 0.0)
   latitude = atan(_y / lengthXZ);
  else{
     if( _y > 0.0)
      latitude = M_PI / 2.0;
     else latitude = -M_PI / 2.0;
  }
  return latitude / M_PI * 180.0;
}

GLdouble GLVector::longitude()const{
  GLdouble longitude;
  if(_z == 0.0){
      if(_x > 0.0)
         longitude = M_PI / 2.0;
      else longitude = -M_PI / 2.0;
    }
  else longitude = atan(_x / _z);
  if((_z < 0.0) & (_x > 0.0))
   longitude += M_PI;
  if((_x < 0.0) & (_z < 0.0))
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
  _x = radius * sin(radLongitude)* cos(radLatitude);
  _y = radius * sin(radLatitude);
  _z = radius * cos(radLongitude)* cos(radLatitude);
}

const GLVector GLVector::normalVector(const GLVector& v)const{
 return vectorMult(v).unitVector();
}

const GLVector GLVector::unitVector()const{
 GLdouble aLength;
 aLength= length();
 if (length() != 0.0)
  return GLVector(_x / length(),
                  _y / length(),
                  _z / length());
  else {
   return GLVector();
  }
}

const GLVector GLVector::vectorMult( const GLVector& v)const{
 return GLVector(
   _y * v.z() - _z * v.y(),
   _z * v.x() - _x * v.z(),
   _x * v.y() - _y * v.x());
}

const GLVector GLVector::operator -(const GLVector& v)const{
    return GLVector(_x - v.x(), _y - v.y(), _z - v.z());
}

const GLVector GLVector::operator +(const GLVector& v)const{
    return GLVector(_x + v.x(), _y + v.y(), _z + v.z());
}

GLdouble GLVector::operator *(const GLVector &v )const{
    return  _x * v.x() + _y * v.y() + _z * v.z();
}

GLVector GLVector::operator *(const GLdouble d )const{
    return  GLVector(_x * d, _y * d, _z * d);
}

const GLVector operator *(GLdouble d, const GLVector &v){
    return v * d;
}

GLVector GLVector::operator = (const GLVector & v){
    if(this != &v){
        _x = v.x();
        _y = v.y();
        _z = v.z();
    }
    return *this;
}

bool GLVector::operator != (const GLVector &v) const{
 return ! (*this == v);
}

bool GLVector::operator == (const GLVector &v) const{
 return ((v.x() == _x) & (v.y() == _y) & (v.z() == _z));
}

GLdouble GLVector::length()const{
    return sqrt(_x*_x + _y*_y + _z*_z);
}
