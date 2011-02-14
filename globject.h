#include <QString>
#include "glcolor.h"

#ifndef GLOBJECT_H
#define GLOBJECT_H

class GLObject
{
public:
    void setID( QString objectID ){ _objectID = objectID; }
    void setColor( GLColor color ){ _color = color; }
    void setColor( float red, float green, float blue ){ _color.setColors(red, green, blue); }
    void setID_Color( QString objectID, GLColor color ){ _objectID = objectID;
                                                         _color    = color; }
    void setTime( float time ){ _time = time; }
    void setID_Color_Time( QString objectID, GLColor color, float time ){ _objectID = objectID;
                                                                          _color    = color;
                                                                          _time     = time; }
    virtual void draw() = 0;

protected:
    QString _objectID;
    GLColor _color;
    float _time;
};

#endif // GLOBJECT_H
