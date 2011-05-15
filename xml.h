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
};

#endif // XML_H
