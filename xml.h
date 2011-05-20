#ifndef XML_H
#define XML_H
#include <QList>
#include "globject.h"

class XML
{
public:

    /*! \brief readXML is used to read all tags from the XML-File.
     *
     *
     *  This method is used to read all tags from the XML-File.
     *  \return The method returns an objectList.
     */
    static QList<GLObject*> readXML(const QString &path);
    static bool    error()    { return _error;     }
    static QString errorText(){ return _errorText; }

private:
    static bool    _error;
    static QString _errorText;
};

#endif // XML_H
