/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLANGLE_H
#define GLANGLE_H

#include "globject.h"
#include "glvector.h"
// bogenmaß !!

//! The Angle class.
/*!
    This class calculates and shows the angle between two vectors.
 */
class GLAngle : public GLObject
{
public:
    //! Constructor of the GLAngle class with two vectors.
    /*!
        Initialize with the two vectors.
        \param vectorA Vector
        \param vectorB Vector
        \param color Object color
        \param objectID Object id
        \param time Time to show object
        \see GLVector
        \see GLColor
     */
    GLAngle( GLVector * vectorA, GLVector * vectorB, GLColor color, QString objectID, int time );

    //! Return the first vector of the angle.
    /*!
        \return The first angle vector
        \see GLVector
     */
    GLVector &vectorA(){ return _vectorA; }

    //! Return the second vector of the angle.
    /*!
        \return The second angle vector
        \see GLVector
     */
    GLVector &vectorB(){ return _vectorB; }

    //! The angle fromXML method is used to fetch specified tags from the XML-File.
    /*!
        This method fetches a specified amount of tags, the most important being:

        -# The id.
        -# Two points.
        -# The color.
        -# The time in msec.
        \param object XML object
        \return Pointer of new angle object
     */
    static GLAngle * fromXml(const QDomElement &object, QList<GLObject*> &objects);

protected:
    //! Draw the object.
    void glObject();

    //! Draw the object id text.
    void glObjectId();

    //! Draw the object coordinate text.
    void glCoordinate();

private:
    GLVector _vectorA;     //!< Vector A \see GLVector
    GLVector _vectorB;     //!< Vector B \see GLVector
    GLVector _vectorMid;   //!< Vector between Vector A and B \see GLVector
    GLVector _vectorLeft;  //!< Vector A \see GLVector
    GLVector _vectorRight; //!< Vector B \see GLVector

    bool _valid;         //!< Validation status of the angle
};

#endif // GLANGLE_H
