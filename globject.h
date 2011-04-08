#include <QString>
#include "glcolor.h"

#ifndef GLOBJECT_H
#define GLOBJECT_H

class GLObject
{
public:
    GLObject( GLColor color = GLColor(), QString objectID = "", int time = 0 ){ _objectID = objectID;
                                                                                _color    = color;
                                                                                _time     = time; }

    GLObject( const GLObject &o ){ if(this != &o){ _color = o.color(); _objectID = o.id(); _time = o.time(); } }

    void setID    ( QString objectID ){ _objectID = objectID; }
    void setColor ( GLColor color    ){ _color    = color;    }
    void setColor ( float redF, float greenF, float blueF ){ _color.setColors(redF, greenF, blueF); }
    void setTime  ( int time         ){ _time     = time;     }
    void setValues( QString objectID, GLColor color = GLColor(), int time = 0 ){ _objectID = objectID;
                                                                                      _color    = color;
                                                                                      _time     = time; }
    QString id()   const{ return _objectID; }
    GLColor color()const{ return _color;    }
    int     time() const{ return _time;     }

    virtual void draw() = 0;

protected:
    QString _objectID;
    GLColor _color;
    int     _time;
};

#endif // GLOBJECT_H
