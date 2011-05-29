/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLDELETE_H
#define GLDELETE_H

#include "globject.h"

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
        \param objects Objects to delete
        \param objectID ID of this object
        \param time Time to draw this object
        \see GLObject
     */
    GLDelete(QList<GLObject *> objects, QString objectID, int time);

    //! Return delete objects.
    /*!
        \return objects to delete
        \see GLObject
     */
    QList<GLObject *> objects(){ return _objects; }

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
    QList<GLObject *> _objects; //!< Objects to delete

protected:
    //! Delete the object
    virtual void glObject();
};

#endif // GLDELETE_H
