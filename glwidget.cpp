#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
        : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f (0.0, 1.0, 0.0);
     glPushMatrix();
     //glRotatef(-1.0, 0.0, 0.0, 0.1);
     glBegin (GL_LINES);
        glVertex2f (-0.5, 0.5);
        glVertex2f (0.5, -0.5);
     glEnd ();
     glPopMatrix();

     glColor3f (0.0, 0.0, 1.0);
     glPushMatrix();
     //glRotatef(1.0, 0.0, 0.0, 0.1);
     glBegin (GL_LINES);
        glVertex2f (0.5, 0.5);
        glVertex2f (-0.5, -0.5);
     glEnd ();
     glPopMatrix();

     glFlush();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}
