#include "globject.h"

GLObject::GLObject( ObjectType type, GLColor color, QString objectID, int time )
{
    _type     = type;
    _objectID = objectID;
    _color    = color;
    _time     = time;
    _draw     = true;
}

GLObject::GLObject( const GLObject &o )
{
    if(this != &o)
    {
        _type     = o.type();
        _color    = o.color();
        _objectID = o.id();
        _time     = o.time();
        _draw     = o.isDrawing();
    }
}

void GLObject::setID( QString objectID )
{
    _objectID = objectID;
}

void GLObject::setColor( GLColor color )
{
    _color    = color;
}

void GLObject::setColor( float redF, float greenF, float blueF )
{
    _color.setColorsF(redF, greenF, blueF);
}

void GLObject::setTime( int time )
{
    _time     = time;
}

void GLObject::setValues( QString objectID, GLColor color, int time )
{
    _objectID = objectID;
    _color    = color;
    _time     = time;
}

void GLObject::setDraw(bool draw)
{
    _draw = draw;
}

void GLObject::draw()
{
    if(_draw)
    {
        glObject();
    }
    else
    {
        _draw = true;
    }
}

void GLObject::drawObjectId()
{
    if(_draw)
    {
        glObjectId();
    }
}

void GLObject::drawCoordinate()
{
    if(_draw)
    {
        glCoordinate();
    }
}

void GLObject::drawVector()
{
    if(_draw)
    {
        glVector();
    }
}
