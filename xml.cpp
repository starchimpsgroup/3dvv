#include "xml.h"
#include <QFile>
#include <QDomDocument>
#include <QProgressDialog>
#include "glpoint.h"
#include "glvector.h"
#include "glplane.h"
#include "gldelete.h"
#include "glangle.h"
#include "glline.h"

bool    XML::_error     = false;
QString XML::_errorText = "";

QList<GLObject*> XML::readXML(const QString &path)
{
    _error     = false;
    _errorText = "";

    QDomDocument doc("vd");
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
    {
        _error     = true;
        _errorText = "Can not open XML-File!";
        return QList<GLObject*>();
    }

    QString xmlError;
    int     xmlErrorLine;

    if (!doc.setContent(&file,false,&xmlError,&xmlErrorLine))
    {
        _error     = true;
        _errorText = "XML parser error: " + xmlError + "<br/>"
                     "Line: " + QString::number(xmlErrorLine);

        file.close();
        return QList<GLObject*>();
    }

    QDomElement root = doc.documentElement();

    if( root.tagName() != "vd" )
    {
        _error     = true;
        _errorText = "XML root tag is not valid!";
        return QList<GLObject*>();
    }

    QList<GLObject*> objectList;
    QDomNode node = root.firstChild();

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
            else if (type == "line")
                objectList.append(GLLine::fromXml(object));
            else if (type == "angle")
                objectList.append(GLAngle::fromXml(object, objectList));
            else if (type == "delete")
                objectList.append(GLDelete::fromXml(object, objectList));

        }

        for(int i = 0; i < objectList.size()-1; i++)
        {
            if(objectList.at(i)->id() == objectList.last()->id())
            {
                _error     = true;
                _errorText = "Another object with this id was found!<br/>"
                             "Line: " + QString::number(node.lineNumber()) + ", ID: " + objectList.last()->id();
                qDeleteAll(objectList);
                return QList<GLObject*>();
            }
        }

        node = node.nextSibling();        
        count++;
    }

    return objectList;
}
