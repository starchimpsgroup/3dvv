/***************************************************************************
 *   Copyright (C) 2007 by Walter Roth                                     *
 *   info@fh-swf.de                                                        *
 *                                                                         *
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLPERSPECTIVE_H
#define GLPERSPECTIVE_H

#include <qgl.h>
#include "glvector.h"

//! A class for encapsulating all data for a gluPerspective and a gluLookAt call.
/*!
These include:
_Fovy: Opening angle of frustum in y-direction (45° is a good average to start with)
_Aspect: The aspect ratio of the viewport (width / height)
_Near and _Far clipping plane distances
_Center: The 3d-point to appear in the center of the viewport
_Camera: The 3d-point where the camera is
_Up: The 3d-vector that points upwards in the viewport

Use the apply() function to transfer the perspective settings to the OpenGL matrices.
 */
class GLPerspective{
public:
    //! Constructor of the GLPerspective class.
    /*!
        Initialize the parameters.
     */
    GLPerspective();

    //! Applies the perspective settings to projection and modelview matrices.
    /*!
        Old matrix values will be overwritten. To be called once before rendering the scene.
     */
    void apply();

    //! Moves the camera on a meridian without modifying the distance to _Center.
    /*!
         Maximum angle is +90 (north), minimum is -90 (south).
         \param angleIncrement Add a positiv or negativ falue
     */
    void turnCameraUpDown( double angleIncrement );

    //! Moves the camera on a latitude without modifying the distance to _Center.
    /*!
         Maximum angle is +180 (east), minimum is -180 (west).
         \param angleIncrement Add a positiv or negativ falue
     */
    void turnCameraLeftRight( double angleIncrement );

    //! Multiply camera vector by factor.
    /*!
        Multiply camera vector by factor
        \param factor Multiplier
     */
    void stretchCameraDistance( double factor );

    //! Shift the whole scene in y direction.
    /*!
        Shift the whole scene in y direction
        \param distance Multiplier
     */
    void shiftSceneUpDown( double distance );

    //! Shift the whole scene in x-z plane orthogonal to camera vector.
    /*!
        Shift the whole scene in x-z plane orthogonal to camera vector
        \param distance Multiplier
     */
    void shiftSceneLeftRight( double distance );

    //! Shift the whole scene in x-z plane parallel to camera vector projection in xz plane.
    /*!
        Shift the whole scene in x-z plane parallel to camera vector
        \param distance Multiplier
     */
    void shiftSceneForwardBackward( double distance );

    void setCamera( const GLVector & newValue );
    void setCenter( const GLVector & newValue );
    void setUp    ( const GLVector & newValue );

    void setAspect( GLdouble newValue );
    void setFar   ( GLdouble newValue );
    void setFovy  ( GLdouble newValue );
    void setNear  ( GLdouble newValue );

    //! Sets viewport and adjusts _Aspect to new viewport
    /*!
        \param width Viewport width
        \param height Viewport height
     */
    void setViewport(int width, int height);

    double distance()const{ return (_Camera - _Center).length(); }
    const GLVector * camera(){ return &_Camera; }const
    GLVector center(){ return _Center; }

    void reset(){ _Camera = 5.0 * v_XYZ; _Center = v_Zero; }
protected:
    GLVector _Camera;
    GLVector _Center;
    GLVector _Up;
    GLdouble _Aspect;
    GLdouble _Far;
    GLdouble _Fovy;
    GLdouble _Near;
    GLint    _Width;  //!< Viewport width
    GLint    _Height; //!< Viewport height
};

#endif
