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

    /**
      * Tests
      */
    //drawCornerMarks();

    // E
    /*GLColor E(1.0,0.0,0.5);

    GLVector e(1,0,0,1,5,0);
    e.setColor(E);
    e.draw();

    GLVector e1(1,5,0,4,5,0);
    e1.setColor(E);
    e1.draw();

    GLVector e2(4,5,0,4,4,0);
    e2.setColor(E);
    e2.draw();

    GLVector e3(4,4,0,2,4,0);
    e3.setColor(E);
    e3.draw();

    GLVector e4(2,4,0,2,3,0);
    e4.setColor(E);
    e4.draw();

    GLVector e5(2,3,0,4,3,0);
    e5.setColor(E);
    e5.draw();

    GLVector e6(4,3,0,4,2,0);
    e6.setColor(E);
    e6.draw();

    GLVector e7(4,2,0,2,2,0);
    e7.setColor(E);
    e7.draw();

    GLVector e8(2,2,0,2,1,0);
    e8.setColor(E);
    e8.draw();

    GLVector e9(2,1,0,4,1,0);
    e9.setColor(E);
    e9.draw();

    GLVector e10(4,1,0,4,0,0);
    e10.setColor(E);
    e10.draw();

    GLVector e11(4,0,0,1,0,0);
    e11.setColor(E);
    e11.draw();

    // N
    GLColor N(1.0,0.5,0.0);

    GLVector n(5,0,0,5,5,0);
    n.setColor(N);
    n.draw();

    GLVector n1(5,5,0,6,5,0);
    n1.setColor(N);
    n1.draw();

    GLVector n2(6,5,0,7,2,0);
    n2.setColor(N);
    n2.draw();

    GLVector n3(7,2,0,7,5,0);
    n3.setColor(N);
    n3.draw();

    GLVector n4(7,5,0,8,5,0);
    n4.setColor(N);
    n4.draw();

    GLVector n5(8,5,0,8,0,0);
    n5.setColor(N);
    n5.draw();

    GLVector n6(8,0,0,7,0,0);
    n6.setColor(N);
    n6.draw();

    GLVector n7(7,0,0,6,3,0);
    n7.setColor(N);
    n7.draw();

    GLVector n8(6,3,0,6,0,0);
    n8.setColor(N);
    n8.draw();

    GLVector n9(6,0,0,5,0,0);
    n9.setColor(N);
    n9.draw();

    // D
    GLColor D(0.0,0.5,1.0);

    GLVector d(9,0,0,9,5,0);
    d.setColor(D);
    d.draw();

    GLVector d1(9,5,0,11,5,0);
    d1.setColor(D);
    d1.draw();

    GLVector d2(11,5,0,12,4,0);
    d2.setColor(D);
    d2.draw();

    GLVector d3(12,4,0,12,1,0);
    d3.setColor(D);
    d3.draw();

    GLVector d4(12,1,0,11,0,0);
    d4.setColor(D);
    d4.draw();

    GLVector d5(11,0,0,9,0,0);
    d5.setColor(D);
    d5.draw();

    GLVector d6(10,1,0,10,4,0);
    d6.setColor(D);
    d6.draw();

    GLVector d7(10,4,0,11,4,0);
    d7.setColor(D);
    d7.draw();

    GLVector d8(11,4,0,11,1,0);
    d8.setColor(D);
    d8.draw();

    GLVector d9(11,1,0,10,1,0);
    d9.setColor(D);
    d9.draw();

    // E2
    GLColor E2(0.5,1.0,0.0);

    GLVector eb(13,0,0,13,5,0);
    eb.setColor(E2);
    eb.draw();

    GLVector eb1(13,5,0,16,5,0);
    eb1.setColor(E2);
    eb1.draw();

    GLVector eb2(16,5,0,16,4,0);
    eb2.setColor(E2);
    eb2.draw();

    GLVector eb3(16,4,0,14,4,0);
    eb3.setColor(E2);
    eb3.draw();

    GLVector eb4(14,4,0,14,3,0);
    eb4.setColor(E2);
    eb4.draw();

    GLVector eb5(14,3,0,16,3,0);
    eb5.setColor(E2);
    eb5.draw();

    GLVector eb6(16,3,0,16,2,0);
    eb6.setColor(E2);
    eb6.draw();

    GLVector eb7(16,2,0,14,2,0);
    eb7.setColor(E2);
    eb7.draw();

    GLVector eb8(14,2,0,14,1,0);
    eb8.setColor(E2);
    eb8.draw();

    GLVector eb9(14,1,0,16,1,0);
    eb9.setColor(E2);
    eb9.draw();

    GLVector eb10(16,1,0,16,0,0);
    eb10.setColor(E2);
    eb10.draw();

    GLVector eb11(16,0,0,13,0,0);
    eb11.setColor(E2);
    eb11.draw();*/

    // bsp

    GLVector v1(3,2,-3);
    v1.setColor(0.5,1.0,0.0);
    v1.draw();

    GLVector v2(3,2,-3,4,4,-3);
    v2.setColor(1.0,0.5,0.0);
    v2.draw();

    GLVector v3(4,4,-3);
    v3.setColor(0.0,0.5,1.0);
    v3.draw();

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
