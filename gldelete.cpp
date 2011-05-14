#include "gldelete.h"

GLDelete::GLDelete(GLObject * object, QString objectID, int time) : GLObject(GLObject::DELETE, GLColor(), objectID, time)
{
    _object = object;
}
