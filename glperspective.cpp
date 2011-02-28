/***************************************************************************
 *   Copyright (C) 2007 by walter                                          *
 *   walter@HP2100-Roth                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "glperspective.h"

GLPerspective::GLPerspective()
{
  _Center = v_Zero;
  _Camera = 5.0 * v_XYZ;
  _Up = v_Y;
  _Fovy = 45.0;
  _Aspect = 1.0;
  _Near = 1.0;
  _Far = 100.0;
}

GLPerspective::~GLPerspective()
{
}

/** Applies the perspective settings to projection and modelview matrices.
  * Old matrix values will be overwritten. To be called once before rendering the scene.
  */
void GLPerspective::apply(){
  glMatrixMode(GL_PROJECTION); // switch to projection matrix
  glLoadIdentity();            // initialize matrix with identity matrix
                               // multipy perspective transformation on projection matrix
  gluPerspective(_Fovy,        // fovy
                 _Aspect,      // aspect
                 _Near,        // near
                 _Far);        // far
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(_Camera.x(), _Camera.y(), _Camera.z(), // eye
            _Center.x(), _Center.y(), _Center.z(), // center
            _Up.x(), _Up.y(), _Up.z());            // up
}

/**
  * Moves the camera on a meridian without modifying the distance to _Center
  * Maximum angle is +90 (north), minimum is -90 (south)
  */
void GLPerspective::turnCameraUpDown( double angleIncrement)  {
  double radius, longitude, latitude;
  GLVector dist = _Camera - _Center;
  radius= dist.length();    // use getters for coordinate transformation
  longitude = dist.longitude();
  latitude = dist.latitude() + angleIncrement;
  if(latitude > 90.0)       // no flying over the poles
   latitude = 90.0;
  if (latitude < -90.0)
   latitude = -90.0;
  dist.setRadiusLongitudeLatitude(radius, longitude,latitude);
  setCamera(_Center + dist); // add dist to get new cam,era position
}
/**
  * Moves the camera on a latitude without modifying the distance to _Center
  * Maximum angle is +180 (east), minimum is -180 (west)
  */
void GLPerspective::turnCameraLeftRight( double angleIncrement){
  double radius, longitude, latitude;
  GLVector dist = _Camera - _Center;
  radius= dist.length();
  longitude = dist.longitude() + angleIncrement;
  if(longitude > 180.0)
   longitude -= 360.0;
  if (longitude < -180.0)
   longitude += 360.0;
  latitude = dist.latitude();
  dist.setRadiusLongitudeLatitude(radius, longitude,latitude);
  setCamera(_Center + dist);
}

/**
  * Setters
  */
void GLPerspective::setCamera(const GLVector & newValue){
   _Camera = newValue;
}
void GLPerspective::setCenter(const GLVector & newValue){
 _Center = newValue;
}
void GLPerspective::setUp(const GLVector & newValue){
 _Up = newValue;
}
void GLPerspective::setAspect(GLdouble newValue){
  _Aspect = newValue;
}
void GLPerspective::setFar(GLdouble newValue){
 _Far = newValue;
}

void GLPerspective::setFovy(GLdouble newValue){
 _Fovy = newValue;
}
void GLPerspective::setNear(GLdouble newValue){
 _Near = newValue;
}

void GLPerspective::setViewport(int width, int height){
  _Width = width;
  _Height = height;
  glViewport(0,0, _Width, _Height);
  _Aspect = (double)_Width / (double)_Height;
}
/**
  * Multiply camera vector by factor
  */
void GLPerspective::stretchCameraDistance(double factor)
{
  GLVector dist = _Camera - _Center;
  dist = dist * factor;
  setCamera(_Center + dist);
}
/**
  *Shift the whole scene in y direction
  */
void GLPerspective::shiftSceneUpDown(double distance)
{
 GLVector vShift = distance * _Up;
 _Center = _Center + vShift;
 _Camera = _Camera + vShift;
}
/**
  *Shift the whole scene in x-z plane orthogonal to camera vector
  */
void GLPerspective::shiftSceneLeftRight(double distance)
{
 GLVector vShift = (_Center - _Camera).normalVector(_Up) * distance;
 _Center = _Center + vShift;
 _Camera = _Camera + vShift;
}
/**
  * Shift the whole scene in x-z plane parallel to camera vector projection in xz plane
  */
void GLPerspective::shiftSceneForwardBackward(double distance)
{
 GLVector vShift = GLVector(_Center.x() -_Camera.x(), _Center.y() -_Camera.y(), 0).unitVector() * distance;
 _Center = _Center + vShift;
 _Camera = _Camera + vShift;
}
