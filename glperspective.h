/***************************************************************************
 *   Copyright (C) 2007 by Walter Roth                                     *
 *   info@fh-swf.de                                                        *
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
#ifndef GLPERSPECTIVE_H
#define GLPERSPECTIVE_H

#include <qgl.h>

#include "glvector.h"
/**
A class for encapsulating all data for a gluPerspective and a gluLookAt call. These include:
_Fovy: Opening angle of frustum in y-direction (45° is a good average to start with)
_Aspect: The aspect ratio of the viewport (width / height)
_Near and _Far clipping plane distances
_Center: The 3d-point to appear in the center of the viewport
_Camera: The 3d-point where the camera is
_Up: The 3d-vector that points upwards in the viewport

Use the apply() function to transfer the perspective settings to the OpenGL matrices.

        @author walter <walter@HP2100-Roth>
*/
class GLPerspective{
public:
    GLPerspective();

    ~GLPerspective();
    /** Applies the perspective settings to projection and modelview matrices.
      * Old matrix values will be overwritten. To be called once before rendering the scene.
      */
     void apply();

    /**Moves the camera on a meridian without modifying the distance to _Center
     * Maximum angle is +90 (north), minimum is -90 (south)
     */
     void turnCameraUpDown( double angleIncrement);
    /**Moves the camera on a latitude without modifying the distance to _Center
     * Maximum angle is +180 (east), minimum is -180 (west)
     */
     void turnCameraLeftRight( double angleIncrement);
    /**Multiply camera vector by factor
    */
    void stretchCameraDistance(double factor);
    /**Shift the whole scene in y direction
    */
    void shiftSceneUpDown(double distance);
    /**Shift the whole scene in x-z plane orthogonal to camera vector
    */
    void shiftSceneLeftRight(double distance);
    /**Shift the whole scene in x-z plane parallel to camera vector projection in xz plane
    */
    void shiftSceneForwardBackward(double distance);

 /**Setters*/
    void setCamera(const GLVector & newValue);
    void setCenter(const GLVector & newValue);
    void setUp(const GLVector & newValue);

    void setAspect(GLdouble newValue);
    void setFar(GLdouble newValue);
    void setFovy(GLdouble newValue);
    void setNear(GLdouble newValue);
    /** Sets viewport and adjusts _Aspect to new viewport
     */
    void setViewport(int width, int height);
/**Getters*/
    double distance()const{ return (_Camera - _Center).length(); }
    GLVector camera(){ return _Camera; }
    GLVector center(){ return _Center; }
    GLdouble aspect(){ return _Aspect; }
    GLdouble far()   { return _Far;    }
    GLdouble fovy()  { return _Fovy;   }
    GLdouble near()  { return _Near;   }

    void reset(){ _Camera = _Camera_backup; _Center = _Center_backup; }
protected:
    GLVector _Camera;
    GLVector _Center;
    GLVector _Camera_backup;
    GLVector _Center_backup;
    GLVector _Up;
    GLdouble _Aspect;
    GLdouble _Far;
    GLdouble _Fovy;
    GLdouble _Near;
    /**Viewport width
     */
    GLint _Width;
    /**Viewport height
      */
    GLint _Height;
};

#endif
