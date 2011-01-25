#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
        : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    _perspective = new GLPerspective();
    setFocusPolicy ( Qt::StrongFocus );
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
    _perspective->apply();

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

    /**
      * clear both the color buffer and the depth buffer
      **/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -5);

    glColor3f (0.0, 1.0, 0.0);
    glPushMatrix(); // Legen die aktuelle Matrix auf den Stack
    //glRotatef(-1.0, 0.0, 0.0, 0.1);
    //glPointSize(5.0);
    //glBegin (GL_POINTS);
    glBegin (GL_LINES);
        glVertex3f (0.0, 0.0, 0.0);
        glVertex3f (1.0, 0.0, 0.0);
    glEnd ();
    glPopMatrix();

    glColor3f (0.0, 0.0, 1.0);
    glPushMatrix();
    //glRotatef(1.0, 0.0, 0.0, 0.1);
    //glLineWidth(10.0);
    glBegin (GL_LINES);
        glVertex3f (0.0, 0.0, 0.0);
        glVertex3f (0.0, 1.0, 0.0);
    glEnd ();
    glPopMatrix();

    glColor3f (1.0, 0.0, 0.0);
    glPushMatrix();
    //glRotatef(1.0, 0.0, 0.0, 0.1);
    glBegin (GL_LINES);
        glVertex3f (0.0, 0.0, 0.0);
        glVertex3f (0.0, 0.0, 1.0);
    glEnd ();
    glPopMatrix();

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

    _perspective->setViewport ( width, height );
}
