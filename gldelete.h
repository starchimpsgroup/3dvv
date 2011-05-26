/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLDELETE_H
#define GLDELETE_H

#include "globject.h"
// für mehrere objekte erweitern!!!

//! The Delete class.
/*!
    This class contains an object that would be deleted at a specified time.
 */
class GLDelete : public GLObject
{
public:
    //! Constructor of GLDelete.
    /*!
        Initialize an object to delete.
        \param object Object to delete
        \param objectID ID of this object
        \param time Time to draw this object
        \see GLObject
     */
    GLDelete(GLObject * object, QString objectID, int time);

    //! Return delete object.
    /*!
        \return object to delete
        \see GLObject
     */
    GLObject * object(){ return _object; }

    //! The delete fromXML method is used to fetch specified tags from the XML-File.
    /*!
        This method fetches a specified amount of tags, the most important being:

        -# The id.
        -# The object.
        -# The time in msec.
        \param object XML object
        \param objects List of readed objects
        \return Pointer of new delete object
     */
    static GLDelete * fromXml(const QDomElement &object, QList<GLObject*> &objects);

private:
    GLObject * _object; //!< Object to delete

protected:
    //! Delete the object
    virtual void glObject(){ if(_object != 0){ _object->setDraw(false); } }
};

#endif // GLDELETE_H
