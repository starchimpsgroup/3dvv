/***************************************************************************
 *   Copyright (C) 2007 by Walter Roth                                     *
 *   info@fh-swf.de                                                        *
 *                                                                         *
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLVECTOR_H
#define GLVECTOR_H

#include "qgl.h"
#include "globject.h"

class GLVector : public GLObject
{
public:
    GLVector(GLColor color = GLColor(), QString objectID = "", int time = 0);

    GLVector(GLdouble x, GLdouble y, GLdouble z, GLColor color = GLColor(), QString objectID = "", int time = 0);

    GLVector(const GLVector &v);

    GLVector(GLdouble sX, GLdouble sY, GLdouble sZ, GLdouble eX, GLdouble eY, GLdouble eZ, GLColor color = GLColor(), QString objectID = "", int time = 0);

    GLdouble angle( const GLVector &v );

    GLdouble x()const{ return _eX - _sX; }
    GLdouble y()const{ return _eY - _sY; }
    GLdouble z()const{ return _eZ - _sZ; }

    void setX( GLdouble x ){ _eX = _sX + x; }
    void setY( GLdouble y ){ _eY = _sY + y; }
    void setZ( GLdouble z ){ _eZ = _sZ + z; }

    void setSX( GLdouble sX ){ _sX = sX; }
    void setSY( GLdouble sY ){ _sY = sY; }
    void setSZ( GLdouble sZ ){ _sZ = sZ; }

    GLdouble sX()const{ return _sX; }
    GLdouble sY()const{ return _sY; }
    GLdouble sZ()const{ return _sZ; }
    GLdouble eX()const{ return _eX; }
    GLdouble eY()const{ return _eY; }
    GLdouble eZ()const{ return _eZ; }

    GLdouble length()const;
    GLdouble latitude()const;
    GLdouble longitude()const;

    void setRadiusLongitudeLatitude(GLdouble radius, GLdouble longitude, GLdouble latitude);

    const GLVector normalVector(const GLVector &v)const;
    const GLVector unitVector  (                 )const;
    const GLVector vectorMult  (const GLVector &v)const;

    const GLVector operator -(const GLVector &v)const;
    const GLVector operator +(const GLVector &v)const;
    GLdouble operator       *(const GLVector &v)const;
    GLVector operator       *(const GLdouble  d)const;
    const GLVector operator /(      GLdouble  d)const;
    GLVector operator       =(const GLVector &v);
    bool operator          !=(const GLVector &v)const;
    bool operator          ==(const GLVector &v)const;

    /*!
        \brief The vector fromXML method is used to fetch specified tags from the XML-File.

        This method fetches a specified amount of tags , the most important being:

        \list
            \i id.
            \i Two points.
            \i The color.
            \i The time.
        \endlist
     */
    static GLVector * fromXml(const QDomElement &object);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();
    void glVector();

private:
    GLdouble _sX;
    GLdouble _sY;
    GLdouble _sZ;
    GLdouble _eX;
    GLdouble _eY;
    GLdouble _eZ;
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
