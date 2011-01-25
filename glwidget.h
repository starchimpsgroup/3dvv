#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "glperspective.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    GLPerspective * _perspective;
};

#endif // GLWIDGET_H
