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
#include "glwidget.h"
#include "gltext.h"
#include <math.h>

GLWidget::GLWidget(GLColor backgroundColor, QWidget *parent) : QGLWidget(parent)
{

    _backgroundColor = backgroundColor;
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

    GLdouble angelX = v_Y.angle(*_perspective->camera()) - 90.0;
    GLdouble angelY = v_Z.angle(GLVector(_perspective->camera()->x(), 0.0, _perspective->camera()->z()));

    if(_perspective->camera()->x() < 0)
        angelY *= -1;

    GLText::setAngels(angelX, angelY);

    /**
      * clear both the color buffer and the depth buffer
      **/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _coordinateAxes->draw();

    for(int i = 0; i <= _objectIndex; i++)
    {
        _objects->at(i)->draw();
    }

    /**
      * Tests
      */
    //drawCornerMarks();

    // bsp

    /*GLVector v1(3,2,-3);
    v1.setColor(0.5,1.0,0.0);
    v1.draw();

    GLVector v2(3,2,-3,4,4,-3);
    v2.setColor(1.0,0.5,0.0);
    v2.draw();

    GLVector v3(4,4,-3);
    v3.setColor(0.0,0.5,1.0);
    v3.draw();*/

    //test

    /*GLVector t(1,2,2);
    t.setColor(1,0,1);
    t.draw();

    GLVector t2(1,2,2,4,5,6);
    t2.setColor(0.5,0,1);
    t2.draw();

    GLVector t3(-1,2,2);
    t3.setColor(1,0,1);
    t3.draw();

    GLVector t4(1,-2,2);
    t4.setColor(1,0,1);
    t4.draw();

    GLVector t5(1,2,-2);
    t5.setColor(1,0,1);
    t5.draw();

    GLVector t6(-1,-2,2);
    t6.setColor(1,0,1);
    t6.draw();

    GLVector t7(1,-2,-2);
    t7.setColor(1,0,1);
    t7.draw();

    GLVector t8(-1,2,-2);
    t8.setColor(1,0,1);
    t8.draw();

    GLVector t9(-1,-2,-2);
    t9.setColor(1,0,1);
    t9.draw();

    GLVector t10(0,-2,-2);
    t10.setColor(1,0,1);
    t10.draw();

    GLVector t10a(0,2,-2);
    t10a.setColor(1,0,1);
    t10a.draw();

    GLVector t10b(0,-2,2);
    t10b.setColor(1,0,1);
    t10b.draw();

    GLVector t10c(0,2,2);
    t10c.setColor(1,0,1);
    t10c.draw();

    GLVector t11(0,0,-2);
    t11.setColor(1,0,1);
    t11.draw();

    GLVector t11a(0,0,2);
    t11a.setColor(1,0,1);
    t11a.draw();

    GLVector t12(0,-2,0);
    t12.setColor(1,0,1);
    t12.draw();

    GLVector t12a(0,2,0);
    t12a.setColor(1,0,1);
    t12a.draw();

    GLVector t13(-2,0,0);
    t13.setColor(1,0,1);
    t13.draw();

    GLVector t13a(2,0,0);
    t13a.setColor(1,0,1);
    t13a.draw();

    /*GLVector tx(-1,-2,3,2,0,0);
    tx.setColor(1,0,1);
    tx.draw();

    /*GLVector tx1(5,5,5,0,0,0);
    tx1.setColor(1,0,1);
    tx1.draw();*/

    /*GLVector tx2(3,3,3,3,-3,-3);
    tx2.setColor(1,0,1);
    tx2.draw();

    /*GLVector t14(0,0,0);
    t14.setColor(1,0,1);
    t14.draw();*/

    /*GLPoint p1( 3.0, 3.0, 3.0 );
    p1.setColor(0.5,0.5,0.5);
    p1.draw();

    GLPoint p2( -3.0, 3.0, 3.0 );
    p2.setColor(0.5,0.5,0.0);
    p2.draw();

    /**
      * Tests /
      */

    glFlush();

    //_navigation->repaint();
}

void GLWidget::resizeGL(int width, int height)
{
    _perspective->setViewport ( width, height );
}

void GLWidget::keyPressEvent ( QKeyEvent * ke )
{

    if ( ke->modifiers() & Qt::ShiftModifier )
    {
        switch ( ke->key() )
        {
        case Qt::Key_Left:
            shiftSceneLeftRight ( -1 );
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftLeft" ) );
            break;
        case Qt::Key_Right:
            shiftSceneLeftRight ( 1 );
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftRight" ) );
            break;
        case Qt::Key_Up:
            shiftSceneUpDown ( -1 );
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftUp" ) );
            break;
        case Qt::Key_Down:
            shiftSceneUpDown ( 1 );
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftDown" ) );
            break;
        case Qt::Key_W:
            shiftSceneForwardBackward ( 0.1 );
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftW" ) );
            break;
        case Qt::Key_S:
            shiftSceneForwardBackward ( -0.1 );
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftS" ) );
            break;
        }
    }
    else
    {
        switch ( ke->key() )
        {
        case Qt::Key_Left:
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "Left" ) );
            turnCameraLeftRight ( -1 );
            break;
        case Qt::Key_Up:
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "Up" ) );
            turnCameraUpDown ( 1 );
            break;
        case Qt::Key_Right:
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "Right" ) );
            turnCameraLeftRight ( 1 );
            break;
        case Qt::Key_Down:
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "Down" ) );
            turnCameraUpDown ( -1 );
            break;
        case Qt::Key_PageUp:
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "PageUp" ) );
            stretchCameraDistance ( 1.1 );
            break;
        case Qt::Key_PageDown:
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "PageDown" ) );
            stretchCameraDistance ( 0.9 );
            break;
        case Qt::Key_Space:
            // qDebug ( "Key: %s",qPrintable ( ( QString ) "Reset" ) );
            _perspective->reset();
            repaint();
            break;
        }
    }

    repaint();
}

void GLWidget::wheelEvent ( QWheelEvent * we )
{

    // ---------------------------------------------------------------------------
    //   Mausrad Zoom
    // ---------------------------------------------------------------------------

    if ( we->modifiers() & Qt::ControlModifier )
    {
        // qDebug ( "Key: %s",qPrintable ( ( QString ) "Wheel" ) );
        // qDebug ( "Double: %s", qPrintable ( QString::number ( event->delta() ) ) );

        if ( we->delta() > 0 )
        {
            stretchCameraDistance ( 1.1 );
        }
        else
        {
            stretchCameraDistance ( 0.9 );
        }

        repaint();
        we->accept();
    }
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
    if ( me->modifiers() & Qt::AltModifier )
    {
        // qDebug ( "Mouse: Alt" );

        int x = abs ( _x - me->x() );
        int y = abs ( _y - me->y() );

        if ( _x < me->x() )
        {
            x *= ( -1 );
            //qDebug ( "Double: %s", qPrintable ( QString::number ( x ) ) );
        }

        if ( _y > me->y() )
        {
            y *= ( -1 );
            //qDebug ( "Double: %s", qPrintable ( QString::number ( y ) ) );
        }

        turnCameraLeftRight ( x );
        turnCameraUpDown ( y );

        _x = me->x();
        _y = me->y();

        // qDebug ( "Mouse: LeftButton" );

        repaint();
    }
}

void GLWidget::setBackgroundColor(GLColor color)
{
    glClearColor(color.redF(),color.greenF(),color.blueF(),color.alphaF());
    repaint();
}

void GLWidget::drawCornerMarks()
{
    GLVector center = _perspective->center();
    const GLVector * camera = _perspective->camera();

    GLVector vecNear( 0,0,0, 5,5,5 );

    //GLVector vecNear( center.x(), center.y(), center.z(), camera.x(), camera.y(), camera.z() );

    GLdouble x = tan(_perspective->fovy()/2.0) * vecNear.length();
    qDebug(qPrintable(QString::number(x)));
    GLVector angleX(x,0,-vecNear.z());

    glPointSize(10);

    glPushMatrix();

    glBegin(GL_POINTS);
        glColor3f (0.0f, 0.0f, 0.0f);
        glVertex3f(center.x(), center.y(), center.z());
    glEnd();

    glTranslatef(vecNear.x(), vecNear.y(), vecNear.z());
// ####
    GLVector vectorXZ(vecNear.x(), 0, vecNear.z());

    glBegin(GL_LINES);
    glColor3f (0.0f, 0.0f, 0.0f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(vecNear.x(), vecNear.y(), vecNear.z());

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(vecNear.x(), 0, vecNear.z());
    glEnd();

    GLdouble angleXZ = v_Z.angle(vectorXZ);
    GLdouble angleYZ = vecNear.angle(vectorXZ);

    glRotatef(angleXZ, 0.0, 1.0, 0.0);
    glRotatef(-angleYZ, 1.0, 0.0, 0.0);
// ####
    glBegin(GL_POINTS);
        glColor3f (0.0f, 0.0f, 0.0f);
        glVertex3f(angleX.x(), angleX.y(), angleX.z());

        glColor3f (0.0f, 0.0f, 0.0f);
        glVertex3f(angleX.y(), angleX.x(), angleX.z());
    glEnd();

    //qDebug(qPrintable(QString::number(angleX.x()) + " " + QString::number(angleX.y()) + " " + QString::number(angleX.z())));

    // Kreuz
    glBegin(GL_LINES);

        glColor3f (0.0f, 1.0f, 0.0f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 50.0);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 50.0, 0.0);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(50.0, 0.0, 0.0);

        glColor3f (1.0f, 0.0f, 0.0f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, -50.0);

        glColor3f (0.0f, 1.0f, 0.0f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, -50.0, 0.0);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(-50.0, 0.0, 0.0);
    glEnd();

    /*GLVector vectorXZ(angleX.x(), 0.0, angleX.z());

    GLdouble angleXZ = v_Z.angle(vectorXZ);
    GLdouble angleYZ = angleX.angle(vectorXZ);

    glRotatef(angleXZ, 0.0, 1.0, 0.0);
    glRotatef(angleYZ, 1.0, 0.0, 0.0);*/

    /*GLVector temp = camera.unitVector()/cos(_perspective->fovy());

    qDebug(qPrintable("X: " + QString::number(temp.x())));
    qDebug(qPrintable("Y: " + QString::number(temp.y())));
    qDebug(qPrintable("Z: " + QString::number(temp.z())));
*/
    /*glBegin(GL_POINTS);
        glColor3f (0.0f, 0.0f, 0.0f);
        //glVertex3f(temp.x(), temp.y(), temp.z());

        glVertex3f(x, 0, center.z());
    glEnd();*/

    glPopMatrix();
}
