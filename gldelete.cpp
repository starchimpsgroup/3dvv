#include "gldelete.h"

GLDelete::GLDelete(GLObject * object, QString objectID, int time) : GLObject(GLObject::DELETE_OBJECT, GLColor(), objectID, time)
{
    _object = object;
}

GLDelete * GLDelete::fromXml(const QDomElement &object, QList<GLObject*> &objects)
{
    if (object.isNull() || object.attribute("type","") != "delete")
        return NULL;

    QString id = object.attribute("id","");

    GLObject * obj = 0;

    QDomNodeList objObjects = object.elementsByTagName("object");
    if (! objObjects.isEmpty())
    {
        QDomElement objNode = objObjects.at(0).toElement();
        QString id = objNode.attribute("id", "");

        foreach(GLObject * o, objects)
        {
            if(o->id() == id && o->type() == GLObject::VECTOR_OBJECT)
            {
                obj = o;
                break;
            }
        }
    }

    int time = 0;
    QDomNodeList times = object.elementsByTagName("time");
    if (!times.isEmpty())
    {
        QDomElement timeNode = times.at(0).toElement();
        time = timeNode.text().toInt();
    }

    return new GLDelete(obj,id,time);
}
