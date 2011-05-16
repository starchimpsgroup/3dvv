#include "gldelete.h"

GLDelete::GLDelete(GLObject * object, QString objectID, int time) : GLObject(GLObject::DELETE_OBJECT, GLColor(), objectID, time)
{
    _object = object;
}
