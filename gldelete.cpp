/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "gldelete.h"

GLDelete::GLDelete(QList<GLObject *> objects, QString objectID, int time) : GLObject(GLObject::DELETE_OBJECT, GLColor(), objectID, time)
{
    _objects = objects;
}

void GLDelete::glObject()
{
    if(!_objects.isEmpty())
    {
        foreach(GLObject * o, _objects)
        {
            o->setDraw(false);
        }
    }
}

GLDelete * GLDelete::fromXml(const QDomElement &object, QList<GLObject*> &objects)
{
    if (object.isNull() || object.attribute("type","") != "delete")
        return NULL;

    QString id = object.attribute("id","");

    GLObject * obj;
    QList<GLObject *> objList;

    QDomNodeList objObjects = object.elementsByTagName("object");
    if (! objObjects.isEmpty())
    {
        for(int i = 0; i < objObjects.size(); i++)
        {
            obj = 0;

            QDomElement objNode = objObjects.at(i).toElement();
            QString id = objNode.attribute("id", "");

            foreach(GLObject * o, objects)
            {
                if(o->id() == id && o->type() == GLObject::VECTOR_OBJECT)
                {
                    obj = o;
                    break;
                }
            }

            if(obj != 0)
            {
                objList.append(obj);
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

    return new GLDelete(objList,id,time);
}
