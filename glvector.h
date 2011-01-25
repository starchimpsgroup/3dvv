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
#ifndef GLVECTOR_H
#define GLVECTOR_H

#include "GL/gl.h"

class GLVector
{
public:
    GLVector(){_x=0.0;_y=0.0;_z=0.0;}
    GLVector(GLdouble x,GLdouble y,GLdouble z){_x=x;_y=y;_z=z;}
    GLVector(const GLVector &v);

    GLdouble x()const{ return _x; }
    GLdouble y()const{ return _y; }
    GLdouble z()const{ return _z; }

    GLdouble length()const;
    GLdouble latitude()const;
    GLdouble longitude()const;

    void setRadiusLongitudeLatitude(GLdouble radius, GLdouble longitude, GLdouble latitude);

    const GLVector normalVector(const GLVector& v)const;
    const GLVector unitVector()const;
    const GLVector vectorMult(const GLVector& v)const;

    const GLVector operator -(const GLVector& v)const;
    const GLVector operator +(const GLVector& v)const;
    GLdouble operator *(const GLVector &v )const;
    GLVector operator *(const GLdouble d )const;
    GLVector operator = (const GLVector & v);
    bool operator != (const GLVector& v) const;
    bool operator == (const GLVector& v) const;

private:
    GLdouble _x;
    GLdouble _y;
    GLdouble _z;
};

static GLVector v_Zero = GLVector(0,0,0);
static GLVector v_X    = GLVector(1,0,0);
static GLVector v_Y    = GLVector(0,1,0);
static GLVector v_Z    = GLVector(0,0,1);
static GLVector v_XY   = GLVector(1,1,0);
static GLVector v_YZ   = GLVector(0,1,1);
static GLVector v_XZ   = GLVector(1,0,1);
static GLVector v_XYZ  = GLVector(1,1,1);

const GLVector operator *(GLdouble d, const GLVector &v);

#endif // GLVECTOR_H
