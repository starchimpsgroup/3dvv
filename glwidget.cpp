//#include <QtGui>
//#include <QtOpenGL>

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
    qglClearColor(QColor::fromRgb(255,255,255));
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}
