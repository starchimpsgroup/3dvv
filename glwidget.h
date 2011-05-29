/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glperspective.h"
#include "glcoordinateaxes.h"
#include "glpoint.h"
#include "glplane.h"
#include "gldelete.h"
#include "glline.h"
#include "glangle.h"

//! The Widget class.
/*!
    This class contains the 3D view for the objects and the controlls for the camera
 */
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    //! Constructor of the GLWidget class.
    /*!
        Initialize with a backroundcolor and the values to show the text of objects.
        \param backgroundColor Backround color of the 3D view
        \param showObjectIds Value to show the object ids
        \param showCoordinates Value to show the coordinates
        \param showVectors Value to show vectors
        \param parent Parent of the widget
        \see GLColor
     */
    GLWidget(GLColor backgroundColor = GLColor(),
             bool showObjectIds      = true,
             bool showCoordinates    = true,
             bool showVectors        = true,
             QWidget *parent         = 0);

    //! Destructor of the GLWidget class.
    ~GLWidget();

    //! Reset the camera and the centerpoint of the 3D view.
    void reset();

    //! Set background color.
    /*!
        Set a background color for the 3D view.
        \param color Background color
     */
    void setBackgroundColor(GLColor color);

    //! Set show object ids.
    /*!
        Set the show object ids value.
        Value to show the object id text or not.
        \param value Show object ids value
     */
    void setShowObjectIds(bool value);

    //! Set show coordinates.
    /*!
        Set the show coordinates value.
        Value to show the coordinate text or not.
        \param value Show coordinates value
     */
    void setShowCoordinates(bool value);

    //! Set show vectors.
    /*!
        Set the show vectors value.
        Value to show the vector text or not.
        \param value Show vectros value
     */
    void setShowVectors(bool value);

    //! Set objects.
    /*!
        Set the list of objects, readed from the xml file
        \param objects List of mathematic objects
     */
    void setObjects(QList<GLObject *> * objects){ _objects = objects; }

    //! Set objects index.
    /*!
        Set the index of the actually shown object
        \param index Object index
     */
    void setObjectIndex(int index);

private:
    //! Turn camera up or down.
    /*!
        To turn the camera up or down it must be a positiv or neagtiv angle.
        \param angle Size of the angle to move the camera position
     */
    void turnCameraUpDown          ( double angle    );

    //! Turn camera left or right.
    /*!
        To turn the camera left or right it must be a positiv or neagtiv angle.
        \param angle Size of the angle to move the camera position
     */
    void turnCameraLeftRight       ( double angle    );

    //! Stretch camera distance.
    /*!
        To stretch the camera in different directions it must be a positiv or neagtiv factor.
        \param factor Size of the factor to stretch the camera position
     */
    void stretchCameraDistance     ( double factor   );

    //! Shift scene up or down.
    /*!
        To shift the camera in different directions it must be a positiv or neagtiv distance.
        \param distance Size of the distance to shift the camera position
     */
    void shiftSceneUpDown          ( double distance );

    //! Shift scene left or right.
    /*!
        To shift the camera in different directions it must be a positiv or neagtiv distance.
        \param distance Size of the distance to shift the camera position
     */
    void shiftSceneLeftRight       ( double distance );

    //! Shift scene forward or backward.
    /*!
        To shift the camera in different directions it must be a positiv or neagtiv distance.
        \param distance Size of the distance to shift the camera position
     */
    void shiftSceneForwardBackward ( double distance );

    //! Initialisation of the 3D view.
    void initializeGL              ();

    //! Paint the coordinate axes and the mathematic objects on the 3D view.
    void paintGL                   ();

    //! Sets viewport to the new size.
    /*!
        \param width Viewport width
        \param height Viewport height
     */
    void resizeGL                  ( int width, int height );

    //! Mouse move event
    /*!
        Move the camera position by dragging the mouse.
        \param me Mouse event
     */
    void mouseMoveEvent            ( QMouseEvent * me );

    //! Mouse press event
    /*!
        Set the actual position of the mouse.
        \param me Mouse event
     */
    void mousePressEvent           ( QMouseEvent * me );

    //! Key press event
    /*!
        For using the keys to move the camera or center point position.
        \param ke Key event
     */
    void keyPressEvent             ( QKeyEvent   * ke );

    //! Wheel event
    /*!
        To move the camera forward or backward.
        \param we Wheel event
     */
    void wheelEvent                ( QWheelEvent * we );

private:
    GLPerspective    * _perspective;     //!< Perspective of the 3D view
    GLCoordinateAxes * _coordinateAxes;  //!< Coordinate axes of the 3D view

    GLColor            _backgroundColor; //!< Background color of the 3D view
    bool               _showObjectIds;   //!< Show object ids value
    bool               _showCoordinates; //!< Show coordinates value
    bool               _showVectors;     //!< Show vectors value

    QList<GLObject *> * _objects;        //!< List of mathematic objects
    int _objectIndex;                    //!< Actual object index

    QList<GLObject *>   _objectsSorted;  //!< List of mathematic sorted objects

    int _x;                              //!< Mouse x position
    int _y;                              //!< Mouse y position
};

#endif // GLWIDGET_H
