/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "glwidget.h"
#include "gltext.h"
#include <math.h>

GLWidget::GLWidget(GLColor backgroundColor,
                   bool showObjectIds,
                   bool showCoordinates,
                   bool showVectors,
                   QWidget *parent) : QGLWidget(parent)
{

    _backgroundColor = backgroundColor;
    _showObjectIds   = showObjectIds;
    _showCoordinates = showCoordinates;
    _showVectors     = showVectors;
    _perspective     = new GLPerspective();
    _coordinateAxes  = new GLCoordinateAxes();

    setFocusPolicy ( Qt::StrongFocus );

    _x=0.0;
    _y=0.0;

    _objectIndex = -1;
}

GLWidget::~GLWidget()
{
    delete _perspective;
    delete _coordinateAxes;
}

void GLWidget::initializeGL()
{
    glClearColor(_backgroundColor.redF(),
                 _backgroundColor.greenF(),
                 _backgroundColor.blueF(),
                 _backgroundColor.alphaF());

    glEnable(GL_DEPTH_TEST);          // Tiefentest aktivieren
    glEnable(GL_CULL_FACE);           // Backface Culling aktivieren
}

void GLWidget::paintGL()
{
    _perspective->apply();

    GLdouble angleX = v_Y.angle(*_perspective->camera()) - 90.0;
    GLdouble angleY = v_Z.angle(GLVector(_perspective->camera()->x(), 0.0, _perspective->camera()->z()));

    if(_perspective->camera()->x() < 0)
        angleY *= -1;

    GLText::setAngels(angleX, angleY);

    /**
      * clear both the color buffer and the depth buffer
      **/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _coordinateAxes->draw();

    foreach(GLObject * object, _objectsSorted)
    {
        if(_showObjectIds)
        {
            object->drawObjectId();
        }

        if(_showVectors)
        {
            object->drawVector();
        }

        if(_showCoordinates)
        {
            object->drawCoordinate();
        }
    }

    foreach(GLObject * object, _objectsSorted)
    {
        object->draw();
    }

    glFlush();
}

void GLWidget::resizeGL(int width, int height)
{
    _perspective->setViewport ( width, height );
}

void GLWidget::setObjectIndex(int index)
{
    _objectIndex = index;

    QList<GLObject *> objectsNormal;
    QList<GLObject *> objectsTransparent;

    if(!_objects->isEmpty())
    {
        for(int i = 0; i <= _objectIndex; i++)
        {
            _objects->at(i)->setDraw(true);

            if(_objects->at(i)->type() == GLObject::DELETE_OBJECT)
            {
                _objects->at(i)->draw();
            }
            else if(_objects->at(i)->color().isTransparent())
            {
                objectsTransparent.append(_objects->at(i));
            }
            else
            {
                objectsNormal.append(_objects->at(i));
            }
        }
    }

    _objectsSorted.clear();
    _objectsSorted.append(objectsNormal + objectsTransparent);

    repaint();
}

void GLWidget::keyPressEvent ( QKeyEvent * ke )
{

    if ( ke->modifiers() & Qt::ShiftModifier )
    {
        switch ( ke->key() )
        {
        case Qt::Key_Left:
            shiftSceneLeftRight ( -1 );
            break;
        case Qt::Key_Right:
            shiftSceneLeftRight ( 1 );
            break;
        case Qt::Key_Up:
            shiftSceneUpDown ( 1 );
            break;
        case Qt::Key_Down:
            shiftSceneUpDown ( -1 );
            break;
        case Qt::Key_W:
            shiftSceneForwardBackward ( 0.1 );
            break;
        case Qt::Key_S:
            shiftSceneForwardBackward ( -0.1 );
            break;
        }
    }
    else
    {
        switch ( ke->key() )
        {
        case Qt::Key_Left:
            turnCameraLeftRight ( -1 );
            break;
        case Qt::Key_Up:
            turnCameraUpDown ( 1 );
            break;
        case Qt::Key_Right:
            turnCameraLeftRight ( 1 );
            break;
        case Qt::Key_Down:
            turnCameraUpDown ( -1 );
            break;
        case Qt::Key_PageUp:
            stretchCameraDistance ( 0.9 );
            break;
        case Qt::Key_PageDown:
            stretchCameraDistance ( 1.1 );
            break;
        }
    }

    repaint();
}

void GLWidget::reset()
{
    _perspective->reset();
    repaint();
}

void GLWidget::wheelEvent ( QWheelEvent * we )
{
    if ( we->delta() > 0 )
    {
        stretchCameraDistance ( 0.9 );
    }
    else
    {
        stretchCameraDistance ( 1.1 );
    }

    repaint();
    we->accept();
}

void GLWidget::turnCameraUpDown ( double angle )
{
    _perspective->turnCameraUpDown ( angle );
}

void GLWidget::turnCameraLeftRight ( double angle )
{
    _perspective->turnCameraLeftRight ( angle );
}

void GLWidget::stretchCameraDistance ( double factor )
{
    _perspective->stretchCameraDistance ( factor );
}

void GLWidget::shiftSceneUpDown ( double distance )
{
    _perspective->shiftSceneUpDown ( distance );
}

void GLWidget::shiftSceneLeftRight ( double distance )
{
    _perspective->shiftSceneLeftRight ( distance );
}

void GLWidget::shiftSceneForwardBackward ( double distance )
{
    _perspective->shiftSceneForwardBackward ( distance );
}

void GLWidget::mouseMoveEvent ( QMouseEvent * me )
{
    int x = abs ( _x - me->x() );
    int y = abs ( _y - me->y() );

    if ( _x < me->x() )
    {
        x *= ( -1 );
    }

    if ( _y > me->y() )
    {
        y *= ( -1 );
    }

    turnCameraLeftRight ( x );
    turnCameraUpDown ( y );

    _x = me->x();
    _y = me->y();

    repaint();
}

void GLWidget::setBackgroundColor(GLColor color)
{
    glClearColor(color.redF(),color.greenF(),color.blueF(),color.alphaF());
    repaint();
}

void GLWidget::setShowObjectIds(bool value)
{
    _showObjectIds = value;
    repaint();
}

void GLWidget::setShowCoordinates(bool value)
{
    _showCoordinates = value;
    repaint();
}

void GLWidget::setShowVectors(bool value)
{
    _showVectors = value;
    repaint();
}
