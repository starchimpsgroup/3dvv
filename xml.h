#ifndef XML_H
#define XML_H
#include <QList>
#include "globject.h"

class XML
{
public:
    XML();
    static QList<GLObject*> readXML(const QString &path);
};

#endif // XML_H
