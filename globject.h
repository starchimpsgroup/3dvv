#include <QString>
#include "glcolor.h"
#include <QDomElement>

#ifndef GLOBJECT_H
#define GLOBJECT_H

class GLObject
{
public:
    typedef enum ObjectType
    {
        ANGLE_OBJECT,
        DELETE_OBJECT,
        LINE_OBJECT,
        PLANE_OBJECT,
        POINT_OBJECT,
        VECTOR_OBJECT
    }
    ObjectType;

    GLObject( ObjectType type, GLColor color = GLColor(), QString objectID = "", int time = 0 );
    GLObject( const GLObject &o );

    void setID    ( QString objectID );
    void setColor ( GLColor color    );
    void setColor ( float redF, float greenF, float blueF );
    void setTime  ( int time         );
    void setValues( QString objectID, GLColor color = GLColor(), int time = 0 );
    void setDraw(bool draw);

    QString id()     const{ return _objectID; }
    GLColor color()  const{ return _color;    }
    int time()       const{ return _time;     }
    ObjectType type()const{ return _type;     }

    bool isDrawing() const{ return _draw;     }

    void draw();
    void drawObjectId();
    void drawCoordinate();
    void drawVector();

protected:
    virtual void glObject() = 0;
    virtual void glObjectId(){}
    virtual void glCoordinate(){}
    virtual void glVector(){}

protected:
    QString    _objectID;
    GLColor    _color;
    int        _time;

private:
    bool       _draw;
    ObjectType _type;
};

#endif // GLOBJECT_H
