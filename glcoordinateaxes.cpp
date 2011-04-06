#include "glcoordinateaxes.h"
#include <QDataStream>
#include "gltext.h"

GLCoordinateAxes::GLCoordinateAxes()
{
    GLCoordinateAxes::Range range = {-80,80};

    setRanges( range, range, range );
    setDefaultColors();
}

GLCoordinateAxes::GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                                    const GLCoordinateAxes::Range &rangeY,
                                    const GLCoordinateAxes::Range &rangeZ )
{
    setRanges( rangeX, rangeY, rangeZ );
    setDefaultColors();
}

GLCoordinateAxes::GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                                    const GLCoordinateAxes::Range &rangeY,
                                    const GLCoordinateAxes::Range &rangeZ,
                                    const GLColor &colorX,
                                    const GLColor &colorY,
                                    const GLColor &colorZ )
{
    setRanges( rangeX, rangeY, rangeZ );
    setColors( colorX, colorY, colorZ );
}

void GLCoordinateAxes::setColors( const GLColor &colorX,
                                  const GLColor &colorY,
                                  const GLColor &colorZ )
{
    _colorX = colorX;
    _colorY = colorY;
    _colorZ = colorZ;
}

void GLCoordinateAxes::setRanges( const GLCoordinateAxes::Range &rangeX,
                                  const GLCoordinateAxes::Range &rangeY,
                                  const GLCoordinateAxes::Range &rangeZ)
{
    _rangeX = rangeX;
    _rangeY = rangeY;
    _rangeZ = rangeZ;
}

void GLCoordinateAxes::setDefaultColors()
{
    _colorX = GLColor( 1.0f, 0.0f, 0.0f );
    _colorY = GLColor( 0.0f, 1.0f, 0.0f );
    _colorZ = GLColor( 0.0f, 0.0f, 1.0f );
}

void GLCoordinateAxes::draw()
{
    glPushMatrix(); // Legen die aktuelle Matrix auf den Stack

    glBegin (GL_LINES);

    glColor3f (_colorX.redF(), _colorX.greenF(), _colorX.blueF());
    glVertex3f (_rangeX.rangeBegin, 0.0, 0.0);
    glVertex3f (_rangeX.rangeEnd  , 0.0, 0.0);

    glColor3f (_colorY.redF(), _colorY.greenF(), _colorY.blueF());
    glVertex3f (0.0, _rangeY.rangeBegin, 0.0);
    glVertex3f (0.0, _rangeY.rangeEnd  , 0.0);

    glColor3f (_colorZ.redF(), _colorZ.greenF(), _colorZ.blueF());
    glVertex3f (0.0, 0.0, _rangeZ.rangeBegin);
    glVertex3f (0.0, 0.0, _rangeZ.rangeEnd  );

    glEnd ();

    GLText::draw("-X",
                 _colorX,
                 GLVector(_rangeX.rangeBegin, -0.35, 0.0));

    GLText::draw("X",
                 _colorX,
                 GLVector(_rangeX.rangeEnd, -0.35, 0.0));

    GLText::draw("-Y",
                 _colorY,
                 GLVector(-0.35, _rangeY.rangeBegin, 0.0));

    GLText::draw("Y",
                 _colorY,
                 GLVector(-0.35, _rangeY.rangeEnd, 0.0));

    GLText::draw("-Z",
                 _colorZ,
                 GLVector(0.0, -0.35, _rangeZ.rangeBegin));

    GLText::draw("Z",
                 _colorZ,
                 GLVector(0.0, -0.35, _rangeZ.rangeEnd));

    drawDistanceMarker();

    glPopMatrix();

    glColor3f (_colorX.redF(), _colorX.greenF(), _colorX.blueF());
    drawCylinder(GLVector(_rangeX.rangeBegin + CYLINDERHEIGHT, 0.0, 0.0), v_Y, 270.0);
    drawCylinder(GLVector(_rangeX.rangeEnd   - CYLINDERHEIGHT, 0.0, 0.0), v_Y, 90.0);

    glColor3f (_colorY.redF(), _colorY.greenF(), _colorY.blueF());
    drawCylinder(GLVector(0.0, _rangeY.rangeBegin + CYLINDERHEIGHT, 0.0), v_X, 90.0);
    drawCylinder(GLVector(0.0, _rangeY.rangeEnd   - CYLINDERHEIGHT, 0.0), v_X, 270.0);

    glColor3f (_colorZ.redF(), _colorZ.greenF(), _colorZ.blueF());
    drawCylinder(GLVector(0.0, 0.0, _rangeZ.rangeBegin + CYLINDERHEIGHT), v_Y, 180.0);
    drawCylinder(GLVector(0.0, 0.0, _rangeZ.rangeEnd   - CYLINDERHEIGHT), v_Y, 0.0);
}

void GLCoordinateAxes::drawDistanceMarker()
{
    for( int i=_rangeX.rangeBegin+CYLINDERHEIGHT; i <= (int)_rangeX.rangeEnd-CYLINDERHEIGHT; i++ )
    {
        if( i != 0)
        {
            glBegin(GL_LINES);
            glColor3f (_colorX.redF(), _colorX.greenF(), _colorX.blueF());
            glVertex3f(i,  0.0, 0.0);
            glVertex3f(i, -0.2, 0.0);
            glEnd();
        }

        if( i % 2 )
        {
            GLText::draw(QString::number(i),
                         _colorX,
                         GLVector(i, -0.35, 0.0));
        }
    }

    for( int i=_rangeY.rangeBegin+CYLINDERHEIGHT; i <= (int)_rangeY.rangeEnd-CYLINDERHEIGHT; i++ )
    {
        if( i != 0)
        {
            glBegin(GL_LINES);
            glColor3f (_colorY.redF(), _colorY.greenF(), _colorY.blueF());
            glVertex3f( 0.0, i, 0.0);
            glVertex3f(-0.2, i, 0.0);
            glEnd();
        }

        if( i % 2 )
        {
            GLText::draw(QString::number(i),
                         _colorY,
                         GLVector(-0.35, i, 0.0));
        }
    }

    for( int i=_rangeZ.rangeBegin+CYLINDERHEIGHT; i <= (int)_rangeZ.rangeEnd-CYLINDERHEIGHT; i++ )
    {
        if( i != 0)
        {
            glBegin(GL_LINES);
            glColor3f (_colorZ.redF(), _colorZ.greenF(), _colorZ.blueF());
            glVertex3f (0.0,  0.0, i);
            glVertex3f (0.0, -0.2, i);
            glEnd();
        }

        if( i % 2 )
        {
            GLText::draw(QString::number(i),
                         _colorZ,
                         GLVector(0.0, -0.35, i));
        }
    }
}

void GLCoordinateAxes::drawCylinder( const GLVector &point, const GLVector &around, GLfloat angel )
{
    glPushMatrix();

    glTranslatef(point.x(), point.y(), point.z());

    glRotatef(angel, around.x(), around.y(), around.z());
    gluCylinder(gluNewQuadric(), 0.1, 0, CYLINDERHEIGHT, 16, 4);

    glRotatef(180, 1.0, 0.0, 0.0);
    gluDisk(gluNewQuadric(), 0, 0.1, 16, 4);

    glPopMatrix();
}
