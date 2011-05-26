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

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(GLColor backgroundColor = GLColor(),
             bool showObjectIds      = true,
             bool showCoordinates    = true,
             bool showVectors        = true,
             QWidget *parent         = 0);

    ~GLWidget();

    void reset();

    void setBackgroundColor(GLColor color);
    void setShowObjectIds(bool value);
    void setShowCoordinates(bool value);
    void setShowVectors(bool value);

    void setObjects(QList<GLObject *> * objects){ _objects = objects; }
    void setObjectIndex(int index);

private:
    void turnCameraUpDown          ( double angle    );
    void turnCameraLeftRight       ( double angle    );
    void stretchCameraDistance     ( double factor   );
    void shiftSceneUpDown          ( double distance );
    void shiftSceneLeftRight       ( double distance );
    void shiftSceneForwardBackward ( double distance );

    void initializeGL              ();
    void paintGL                   ();
    void resizeGL                  ( int width, int height );

    void mouseMoveEvent            ( QMouseEvent * me );
    void keyPressEvent             ( QKeyEvent   * ke );
    void wheelEvent                ( QWheelEvent * we );

private:
    GLPerspective    * _perspective;
    GLCoordinateAxes * _coordinateAxes;

    GLColor            _backgroundColor;
    bool               _showObjectIds;
    bool               _showCoordinates;
    bool               _showVectors;

    QList<GLObject *> * _objects;
    int _objectIndex;

    QList<GLObject *>   _objectsSorted;

    int _x;
    int _y;
};

#endif // GLWIDGET_H
