/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef XML_H
#define XML_H
#include <QList>
#include "globject.h"

//! The XML class.
/*!
    This class reads the XML file and adds the objects to a list.
 */
class XML
{
public:

    //! readXML is used to read all tags from the XML-File.
    /*!
        This method is used to read all tags from the XML-File.
        \return The method returns an objectList.
        \param path Path to XML file
     */
    static QList<GLObject*> readXML(const QString &path);

    //! Return error state.
    /*!
        \return Error state, true if an error occurred
     */
    static bool    error()    { return _error;     }

    //! Return error text.
    /*!
        \return Error text, if an error occurred
     */
    static QString errorText(){ return _errorText; }

private:
    static bool    _error;     //!< Error state
    static QString _errorText; //!< Error text
};

#endif // XML_H
