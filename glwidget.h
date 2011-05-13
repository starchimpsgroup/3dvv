/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
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
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glperspective.h"
#include "glcoordinateaxes.h"
#include "glpoint.h"
#include "glplain.h"

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

    void setBackgroundColor(GLColor color);
    void setShowObjectIds(bool value);
    void setShowCoordinates(bool value);
    void setShowVectors(bool value);

    void setObjects(QList<GLObject *> * objects){ _objects = objects; }
    void setObjectIndex(int index){ _objectIndex = index; };

private:
    void turnCameraUpDown          ( double angle    );
    void turnCameraLeftRight       ( double angle    );
    void stretchCameraDistance     ( double factor   );
    void shiftSceneUpDown          ( double distance );
    void shiftSceneLeftRight       ( double distance );
    void shiftSceneForwardBackward ( double distance );

    void drawCornerMarks           ();

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

    QList<GLObject *> _transparentObjects;

    int _x;
    int _y;
};

#endif // GLWIDGET_H
