#ifndef GLDELETE_H
#define GLDELETE_H

#include "globject.h"

class GLDelete : public GLObject
{
public:
    GLDelete(GLObject * object, QString objectID, int time);

    GLObject * object(){ return _object; }

    static GLDelete * fromXml(const QDomElement &object, QList<GLObject*> &objects);

private:
    GLObject * _object;

protected:
    virtual void glObject(){ if(_object != 0){ _object->setDraw(false); } };
};

#endif // GLDELETE_H
