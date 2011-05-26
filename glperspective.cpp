/***************************************************************************
 *   Copyright (C) 2007 by Walter Roth                                     *
 *   info@fh-swf.de                                                        *
 *                                                                         *
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "glperspective.h"

GLPerspective::GLPerspective()
{
    _Center = v_Zero;
    _Camera = 5.0 * v_XYZ;
    _Up     = v_Y;
    _Fovy   = 45.0;
    _Aspect = 1.0;
    _Near   = 1.0;
    _Far    = 10000.0;
}

void GLPerspective::apply()
{
    glMatrixMode(GL_PROJECTION); // switch to projection matrix

    glLoadIdentity();            // initialize matrix with identity matrix, multipy perspective transformation on projection matrix

    gluPerspective(_Fovy,
                   _Aspect,
                   _Near,
                   _Far);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(_Camera.x(), _Camera.y(), _Camera.z(), // eye
              _Center.x(), _Center.y(), _Center.z(), // center
              _Up.x(), _Up.y(), _Up.z());            // up
}

void GLPerspective::turnCameraUpDown( double angleIncrement )
{
    double radius, longitude, latitude;
    GLVector dist = _Camera - _Center;
    radius        = dist.length();
    longitude     = dist.longitude();
    latitude      = dist.latitude() + angleIncrement;

    if(latitude > 90.0)       // no flying over the poles
        latitude = 90.0;
    if (latitude < -90.0)
        latitude = -90.0;

    dist.setRadiusLongitudeLatitude(radius, longitude,latitude);
    setCamera(_Center + dist); // add dist to get new camera position
}

void GLPerspective::turnCameraLeftRight( double angleIncrement )
{
    double radius, longitude, latitude;
    GLVector dist = _Camera - _Center;
    radius        = dist.length();
    longitude     = dist.longitude() + angleIncrement;

    if(longitude > 180.0)
        longitude -= 360.0;
    if (longitude < -180.0)
        longitude += 360.0;

    latitude = dist.latitude();
    dist.setRadiusLongitudeLatitude(radius, longitude,latitude);
    setCamera(_Center + dist);
}

void GLPerspective::setCamera( const GLVector & newValue )
{
    _Camera = newValue;
}

void GLPerspective::setCenter( const GLVector & newValue )
{
    _Center = newValue;
}

void GLPerspective::setUp( const GLVector & newValue )
{
    _Up = newValue;
}

void GLPerspective::setAspect( GLdouble newValue )
{
    _Aspect = newValue;
}
void GLPerspective::setFar( GLdouble newValue )
{
    _Far = newValue;
}

void GLPerspective::setFovy( GLdouble newValue )
{
    _Fovy = newValue;
}

void GLPerspective::setNear( GLdouble newValue )
{
    _Near = newValue;
}

void GLPerspective::setViewport( int width, int height )
{
    _Width  = width;
    _Height = height;

    glViewport(0,0, _Width, _Height);

    _Aspect = (double)_Width / (double)_Height;
}

void GLPerspective::stretchCameraDistance( double factor )
{
    GLVector dist = _Camera - _Center;

    if(factor > 1.0 || (int)dist.length() != 0)
    {
        dist = dist * factor;
        setCamera(_Center + dist);
    }
}

void GLPerspective::shiftSceneUpDown( double distance )
{
    GLVector vShift = distance * _Up;

    _Center = _Center + vShift;
    _Camera = _Camera + vShift;
}

void GLPerspective::shiftSceneLeftRight( double distance )
{
    GLVector vShift = (_Center - _Camera).normalVector(_Up) * distance;

    _Center = _Center + vShift;
    _Camera = _Camera + vShift;
}

void GLPerspective::shiftSceneForwardBackward( double distance )
{
    GLVector vShift = GLVector(_Center.x() -_Camera.x(), _Center.y() -_Camera.y(), 0).unitVector() * distance;

    _Center = _Center + vShift;
    _Camera = _Camera + vShift;
}
