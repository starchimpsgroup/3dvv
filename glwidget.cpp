/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst                                 *
 *   christian@ernst-menden.de                                             *
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

GLWidget::GLWidget(QWidget *parent)
{
    setParent(parent);
    _perspective = new GLPerspective();
    setFocusPolicy ( Qt::StrongFocus );

    _x=0.0;
    _y=0.0;
}

GLWidget::~GLWidget()
{
    delete _perspective;
}

void GLWidget::initializeGL()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glEnable(GL_DEPTH_TEST);          //Tiefentest aktivieren
    glEnable(GL_CULL_FACE);           //Backface Culling aktivieren
}

void GLWidget::paintGL()
{
    //glLoadIdentity ();             /* clear the matrix */
    /**
      * The arguments for this command indicate how the camera should be translated (moved) in the x, y, and z directions.
      **/
    //glTranslatef (0.0f, 0.0f, 0.0f); /* viewing transformation */
    //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */
    //glFlush();

    /*gluPerspective(45.0,
                   1.0,
                   1.0,
                   100.0);*/

    _perspective->apply();

    /**
      * clear both the color buffer and the depth buffer
      **/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    //glTranslatef(0, 0, -5);

    glColor3f (0.0, 1.0, 0.0);
    //glPushMatrix(); // Legen die aktuelle Matrix auf den Stack
    //glRotatef(-1.0, 0.0, 0.0, 0.1);
    //glPointSize(5.0);
    //glBegin (GL_POINTS);
    glBegin (GL_LINES);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (1.0, 0.0, 0.0);
    glEnd ();
    //glPopMatrix();

    glColor3f (0.0, 0.0, 1.0);
    //glPushMatrix();
    //glRotatef(1.0, 0.0, 0.0, 0.1);
    //glLineWidth(10.0);
    glBegin (GL_LINES);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (0.0, 1.0, 0.0);
    glEnd ();
    //glPopMatrix();

    glColor3f (1.0, 0.0, 0.0);
    //glPushMatrix();
    //glRotatef(1.0, 0.0, 0.0, 0.1);
    glBegin (GL_LINES);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (0.0, 0.0, 1.0);
    glEnd ();
    //glPopMatrix();

    glFlush();
}

void GLWidget::resizeGL(int width, int height)
{
    /*glViewport(0,0, width, height); // wie groß die OpenGL-Ausgabe werden soll
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, width/height, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();*/

    //glViewport ( 0, 0, ( GLint ) width, ( GLint ) height );
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
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftLeft" ) );
                                break;
                case Qt::Key_Right:
                                shiftSceneLeftRight ( 1 );
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftRight" ) );
                                break;
                case Qt::Key_Up:
                                shiftSceneUpDown ( -1 );
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftUp" ) );
                                break;
                case Qt::Key_Down:
                                shiftSceneUpDown ( 1 );
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftDown" ) );
                                break;
                case Qt::Key_W:
                                shiftSceneForwardBackward ( 0.1 );
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftW" ) );
                                break;
                case Qt::Key_S:
                                shiftSceneForwardBackward ( -0.1 );
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "ShiftS" ) );
                                break;
                }
        }
        else
        {
                switch ( ke->key() )
                {
                case Qt::Key_Left:
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "Left" ) );
// 			_Perspective->turnCameraEastWest ( -1 );
                                turnCameraLeftRight ( -1 );
                                break;
                case Qt::Key_Up:
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "Up" ) );
// 			_Perspective->turnCameraNorthSouth ( 1 );
                                turnCameraUpDown ( 1 );
                                break;
                case Qt::Key_Right:
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "Right" ) );
// 			_Perspective->turnCameraEastWest ( 1 );
                                turnCameraLeftRight ( 1 );
                                break;
                case Qt::Key_Down:
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "Down" ) );
// 			_Perspective->turnCameraNorthSouth ( -1 );
                                turnCameraUpDown ( -1 );
                                break;
                case Qt::Key_PageUp:
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "PageUp" ) );
// 			_Perspective->multiplyDistance ( 1.1 );
                                stretchCameraDistance ( 1.1 );
                                break;
                case Qt::Key_PageDown:
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "PageDown" ) );
// 			_Perspective->multiplyDistance ( 0.9 );
                                stretchCameraDistance ( 0.9 );
                                break;
                case Qt::Key_Space:
                                qDebug ( "Key: %s",qPrintable ( ( QString ) "Reset" ) );
                                _perspective->reset();
                                repaint();
                                break;
                }
        }

        repaint();
}

void GLWidget::wheelEvent ( QWheelEvent * event )
{

// ---------------------------------------------------------------------------
//   Mausrad Zoom
// ---------------------------------------------------------------------------

        if ( event->modifiers() & Qt::ControlModifier )
        {
                qDebug ( "Key: %s",qPrintable ( ( QString ) "Wheel" ) );
                qDebug ( "Double: %s", qPrintable ( QString::number ( event->delta() ) ) );

                if ( event->delta() > 0 )
                {
                        stretchCameraDistance ( 1.1 );
                }
                else
                {
                        stretchCameraDistance ( 0.9 );
                }

                repaint();
                event->accept();
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
// 	GLVector camera = _Perspective->getCamera();
// 	GLVector center = _Perspective->getCenter();
// 	center.setY ( center.y() + distance );
// 	camera.setY ( camera.y() + distance );
// 	_Perspective->setCamera ( camera );
// 	_Perspective->setCenter ( center );
// 	repaint();

        _perspective->shiftSceneUpDown ( distance );
}

void GLWidget::shiftSceneLeftRight ( double distance )
{
// 	GLVector left ( _Perspective->getCamera() - _Perspective->getCenter() );
// 	left = left.vectorMult ( _Perspective->getUp() ).unitVector();
// 	_Perspective->setCamera ( _Perspective->getCamera() + left * distance );
// 	_Perspective->setCenter ( _Perspective->getCenter() + left * distance );

        _perspective->shiftSceneLeftRight ( distance );
}

void GLWidget::shiftSceneForwardBackward ( double distance )
{
// 	GLVector forward ( _Perspective->getCamera() - _Perspective->getCenter() );
// 	forward = forward.unitVector();
// 	_Perspective->setCamera ( _Perspective->getCamera() + forward * distance );
        //_Perspective->setCenter(_Perspective->getCenter() + forward * distance);

        _perspective->shiftSceneForwardBackward ( distance );
}

void GLWidget::mouseMoveEvent ( QMouseEvent * me )
{
        if ( me->modifiers() & Qt::AltModifier )
        {
                qDebug ( "Mouse: Alt" );

// 		if ( me->buttons() & Qt::LeftButton )
// 		{
// 			qDebug ( "x1: %s", qPrintable ( QString::number ( _x ) ) );
// 			qDebug ( "y1: %s", qPrintable ( QString::number ( _y ) ) );
// 			qDebug ( "x2: %s", qPrintable ( QString::number ( me->x() ) ) );
// 			qDebug ( "y2: %s", qPrintable ( QString::number ( me->y() ) ) );

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

                qDebug ( "Mouse: LeftButton" );

                repaint();
// 		}
        }
}
