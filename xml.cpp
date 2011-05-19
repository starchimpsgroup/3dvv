#include "xml.h"
#include <QFile>
#include <QDomDocument>
#include <QProgressDialog>
#include "glpoint.h"
#include "glvector.h"
#include "glplane.h"
#include "gldelete.h"
#include "glangle.h"

QList<GLObject*> XML::readXML(const QString &path)
{
    QDomDocument doc("vd");
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        return QList<GLObject*>();

    if (!doc.setContent(&file))
    {
        file.close();
        return QList<GLObject*>();
    }

    QDomElement root = doc.documentElement();

    if( root.tagName() != "vd" )
        return QList<GLObject*>();

    QList<GLObject*> objectList;
    QDomNode node = root.firstChild();

    qDebug("size: %i",root.childNodes().size());

    QProgressDialog progress("Read XML-File...", "Cancel", 0, root.childNodes().size());
    progress.setCancelButton(0);
    progress.show();
    int count = 0;

    while (!node.isNull())
    {
        progress.setValue(count);

        if (QDomNode::ElementNode == node.nodeType())
        {
            QDomElement object = node.toElement();
            QString type = object.attribute("type");

            if (type == "point")
                objectList.append(GLPoint::fromXml(object));
            else if (type == "vector")
                objectList.append(GLVector::fromXml(object));
            else if (type == "plane")
                objectList.append(GLPlane::fromXml(object));

        }
        node = node.nextSibling();
        count++;
    }

    return objectList;
}
