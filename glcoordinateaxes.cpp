#include "glcoordinateaxes.h"

GLCoordinateAxes::GLCoordinateAxes()
{
    GLCoordinateAxes::Range range = {-5.0, 5.0};

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
                                    const GLCoordinateAxes::Color &colorX,
                                    const GLCoordinateAxes::Color &colorY,
                                    const GLCoordinateAxes::Color &colorZ )
{
    setRanges( rangeX, rangeY, rangeZ );
    setColors( colorX, colorY, colorZ );
}

void GLCoordinateAxes::setColors( const GLCoordinateAxes::Color &colorX,
                                  const GLCoordinateAxes::Color &colorY,
                                  const GLCoordinateAxes::Color &colorZ )
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
    GLCoordinateAxes::Color colorX = { 1.0, 0.0, 0.0 };
    GLCoordinateAxes::Color colorY = { 0.0, 1.0, 0.0 };
    GLCoordinateAxes::Color colorZ = { 0.0, 0.0, 1.0 };

    setColors( colorX, colorY, colorZ );
}

void GLCoordinateAxes::draw()
{
    glPushMatrix(); // Legen die aktuelle Matrix auf den Stack

    glBegin (GL_LINES);

    glColor3f (_colorX.red, _colorX.green, _colorX.blue);
    glVertex3f (_rangeX.rangeBegin, 0.0, 0.0);
    glVertex3f (_rangeX.rangeEnd  , 0.0, 0.0);

    glColor3f (_colorY.red, _colorY.green, _colorY.blue);
    glVertex3f (0.0, _rangeY.rangeBegin, 0.0);
    glVertex3f (0.0, _rangeY.rangeEnd  , 0.0);

    glColor3f (_colorZ.red, _colorZ.green, _colorZ.blue);
    glVertex3f (0.0, 0.0, _rangeZ.rangeBegin);
    glVertex3f (0.0, 0.0, _rangeZ.rangeEnd  );

    glEnd ();

    glPopMatrix();

    drawDistanceMarker();
}

void GLCoordinateAxes::drawDistanceMarker()
{
    int rangePosition;

    //glPushMatrix(); // Legen die aktuelle Matrix auf den Stack

    glBegin (GL_LINES);

    glColor3f (_colorX.red, _colorX.green, _colorX.blue);
    rangePosition = _rangeX.rangeBegin;
    for( int i=rangePosition; i <= (int)_rangeX.rangeEnd; i++ )
    {
        glVertex3f (i, 0.0, 0.0);
        glVertex3f (i, -0.2, 0.0);
    }

    glColor3f (_colorY.red, _colorY.green, _colorY.blue);
    rangePosition = _rangeY.rangeBegin;
    for( int i=rangePosition; i <= (int)_rangeY.rangeEnd; i++ )
    {
        glVertex3f (0.0, i, 0.0);
        glVertex3f (-0.2, i, 0.0);
    }

    glColor3f (_colorZ.red, _colorZ.green, _colorZ.blue);
    rangePosition = _rangeZ.rangeBegin;
    for( int i=rangePosition; i <= (int)_rangeZ.rangeEnd; i++ )
    {
        glVertex3f (0.0, 0.0, i);
        glVertex3f (0.0, -0.2, i);
    }

    glEnd ();

    glTranslatef(0, 0, 5);

    gluCylinder(gluNewQuadric(), 0.1, 0, 0.3, 16, 4);

    /*GLubyte Font[14]= {
        33,
        0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18
    };

    glBitmap(8,8,0,0,0,0,Font);*/

    //glPopMatrix();
}
