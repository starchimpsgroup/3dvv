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

//! The Vector class.
/*!
    This class contains the start and end point of the vector,
    some functions to calculate with vectors
    and a function to draw the vector in the 3D view.
 */
class GLVector : public GLObject
{
public:
    //! Constructor of the GLVector class.
    /*!
        Initialize only with the color, id and time.
        The start and end point will be set null.
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLColor
     */
    GLVector(GLColor color = GLColor(), QString objectID = "", int time = 0);

    //! Constructor of the GLVector class.
    /*!
        Initialize with the x,y,z coordinates, color, id and time.
        The coordinates are the end point of the vector, so the startpoint will be set null.
        \param x X of end point
        \param y Y of end point
        \param z Z of end point
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLColor
     */
    GLVector(GLdouble x, GLdouble y, GLdouble z, GLColor color = GLColor(), QString objectID = "", int time = 0);

    //! Copy constructor of the GLVector class.
    /*!
        Copy the vector to a new vector.
        \param v Vector to copy
     */
    GLVector(const GLVector &v);

    //! Constructor of the GLVector class.
    /*!
        Initialize with the x,y,z coordinates of the start and endpoint, color, id and time.
        \param sX X of start point
        \param sY Y of start point
        \param sZ Z of start point
        \param eX X of end point
        \param eY Y of end point
        \param eZ Z of end point
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLColor
     */
    GLVector(GLdouble sX, GLdouble sY, GLdouble sZ, GLdouble eX, GLdouble eY, GLdouble eZ, GLColor color = GLColor(), QString objectID = "", int time = 0);

    //! Calculate a angle between two vectors.
    /*!
      Calculate a vector between this and another angle.
        \param v Vector to calculate the angle
     */
    GLdouble angle( const GLVector &v );

    //! Returns and calculates the X value of the vector.
    /*!
        \return X value of angle
     */
    GLdouble x()const{ return _eX - _sX; }

    //! Returns and calculates the Y value of the vector.
    /*!
        \return Y value of angle
     */
    GLdouble y()const{ return _eY - _sY; }

    //! Returns and calculates the Z value of the vector.
    /*!
        \return Z value of angle
     */
    GLdouble z()const{ return _eZ - _sZ; }

    //! Sets the X value of the vector.
    /*!
        \param x X value of the vector
     */
    void setX( GLdouble x ){ _eX = _sX + x; }

    //! Sets the Y value of the vector.
    /*!
        \param y Y value of the vector
     */
    void setY( GLdouble y ){ _eY = _sY + y; }

    //! Sets the Z value of the vector.
    /*!
        \param z Z value of the vector
     */
    void setZ( GLdouble z ){ _eZ = _sZ + z; }

    //! Sets the start X value of the vector.
    /*!
        \param sX Start x value of the vector
     */
    void setSX( GLdouble sX ){ _sX = sX; }

    //! Sets the start Y value of the vector.
    /*!
        \param sY Start y value of the vector
     */
    void setSY( GLdouble sY ){ _sY = sY; }

    //! Sets the start Z value of the vector.
    /*!
        \param sZ Start z value of the vector
     */
    void setSZ( GLdouble sZ ){ _sZ = sZ; }

    //! Returns the start x value of the vector.
    /*!
        \return Start x value of the vector
     */
    GLdouble sX()const{ return _sX; }

    //! Returns the start y value of the vector.
    /*!
        \return Start y value of the vector
     */
    GLdouble sY()const{ return _sY; }

    //! Returns the start z value of the vector.
    /*!
        \return Start z value of the vector
     */
    GLdouble sZ()const{ return _sZ; }

    //! Returns the end x value of the vector.
    /*!
        \return End x value of the vector
     */
    GLdouble eX()const{ return _eX; }

    //! Returns the end y value of the vector.
    /*!
        \return End y value of the vector
     */
    GLdouble eY()const{ return _eY; }

    //! Returns the end z value of the vector.
    /*!
        \return End z value of the vector
     */
    GLdouble eZ()const{ return _eZ; }

    //! Returns the lenght of the vector.
    /*!
        \return Lenght of the vector
     */
    GLdouble length()const;

    //! Returns the latitude of the vector.
    /*!
        \return Latitude of the vector
     */
    GLdouble latitude()const;

    //! Returns the longitude of the vector.
    /*!
        \return Longitude of the vector
     */
    GLdouble longitude()const;

    //! Sets a new radius, longitude and latitude.
    /*!
        This function is used by GLPerspective.
        \param radius New radius
        \param longitude New longitude
        \param latitude New latitude
        \see GLPerspective
     */
    void setRadiusLongitudeLatitude(GLdouble radius, GLdouble longitude, GLdouble latitude);

    //! Normal vector.
    /*!
        Multiplies with the input vector and calculates unit vector.
        \param v Vector to multiply
        \return Normal vector
        \see vectorMult
        \see unitVector
     */
    const GLVector normalVector(const GLVector &v)const;

    //! Unit vector.
    /*!
        Calculate a unit vector.
        \return Unit vector
     */
    const GLVector unitVector  (                 )const;

    //! Vector mult.
    /*!
        Multiplies two vectors.
        \param v Vector to multiply
        \return Multiplied vector
     */
    const GLVector vectorMult  (const GLVector &v)const;

    //! Subtraction for two vectors.
    /*!
        Subtract two vectors.
        \param v Vector to subtract
        \return Subtracted vector
     */
    const GLVector operator -(const GLVector &v)const;

    //! Addition for two vectors.
    /*!
        Addit two vectors.
        \param v Vector to addit
        \return Addited vector
     */
    const GLVector operator +(const GLVector &v)const;

    //! Multiplication for two vectors.
    /*!
        Multiplicate two vectors.
        \param v Vector to multiplicate
        \return Multiplicated vector
     */
    GLdouble operator       *(const GLVector &v)const;

    //! Multiplication for a vectors and a numeral.
    /*!
        Multiplicate a vectors and a numeral.
        \param d Numeral to multiplicate
        \return Multiplicated vector with numeral
     */
    GLVector operator       *(const GLdouble  d)const;

    //! Division for a vectors and a numeral.
    /*!
        Divide a vectors and a numeral.
        \param d Numeral to divide
        \return Divided vector with numeral
     */
    const GLVector operator /(      GLdouble  d)const;

    //! Set the vector equal the another vector.
    /*!
        Copys the values from one to another vector
        \param v Vector to copy
        \return Copied vector
     */
    GLVector operator       =(const GLVector &v);

    //! Check that two vectors are not equal.
    /*!
        \param v Vector to check
        \return Value of not equal
     */
    bool operator          !=(const GLVector &v)const;

    //! Check that two vectors are equal.
    /*!
        \param v Vector to check
        \return Value of equal
     */
    bool operator          ==(const GLVector &v)const;

    //! The vector fromXML method is used to fetch specified tags from the XML-File.
    /*!
        This method fetches a specified amount of tags, the most important being:

        -# The id.
        -# Two points.
        -# The color.
        -# The time in msec.
        \param object XML object
        \return Pointer of new vector object
     */
    static GLVector * fromXml(const QDomElement &object);

protected:
    void glObject();
    void glObjectId();
    void glCoordinate();
    void glVector();

private:
    GLdouble _sX; //!< Start x value of the vector
    GLdouble _sY; //!< Start y value of the vector
    GLdouble _sZ; //!< Start z value of the vector
    GLdouble _eX; //!< End x value of the vector
    GLdouble _eY; //!< End y value of the vector
    GLdouble _eZ; //!< End z value of the vector
};

static GLVector v_Zero = GLVector(0,0,0);
static GLVector v_X    = GLVector(1,0,0);
static GLVector v_Y    = GLVector(0,1,0);
static GLVector v_Z    = GLVector(0,0,1);
static GLVector v_XY   = GLVector(1,1,0);
static GLVector v_YZ   = GLVector(0,1,1);
static GLVector v_XZ   = GLVector(1,0,1);
static GLVector v_XYZ  = GLVector(1,1,1);

//! Multiplication for a vectors and a numeral.
/*!
    Multiplicate a vectors and a numeral.
    \param d Numeral to multiplicate
    \param v Vector to multiplicate
    \return Multiplicated vector with numeral
 */
const GLVector operator *(GLdouble d, const GLVector &v);

#endif // GLVECTOR_H
