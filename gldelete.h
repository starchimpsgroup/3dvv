#ifndef GLDELETE_H
#define GLDELETE_H

#include "globject.h"

class GLDelete : public GLObject
{
public:
    GLDelete(GLObject * object, QString objectID, int time);

private:
    GLObject * _object;

protected:
    virtual void glObject(){ _object->setDraw(false); };
};

#endif // GLDELETE_H
