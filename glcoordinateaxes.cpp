#include "glcoordinateaxes.h"

GLCoordinateAxes::GLCoordinateAxes()
{
    GLCoordinateAxes::Range range = {-5, 5};

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
    _colorX = GLColor( 1.0, 0.0, 0.0 );
    _colorY = GLColor( 0.0, 1.0, 0.0 );
    _colorZ = GLColor( 0.0, 0.0, 1.0 );
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

    drawDistanceMarker();

    glPopMatrix();

}

void GLCoordinateAxes::drawDistanceMarker()
{
    //glPushMatrix(); // Legen die aktuelle Matrix auf den Stack

    glBegin (GL_LINES);

    glColor3f (_colorX.redF(), _colorX.greenF(), _colorX.blueF());
    for( int i=_rangeX.rangeBegin; i <= (int)_rangeX.rangeEnd; i++ )
    {
        glVertex3f (i, 0.0, 0.0);
        glVertex3f (i, -0.2, 0.0);
    }

    glColor3f (_colorY.redF(), _colorY.greenF(), _colorY.blueF());
    for( int i=_rangeY.rangeBegin; i <= (int)_rangeY.rangeEnd; i++ )
    {
        glVertex3f (0.0, i, 0.0);
        glVertex3f (-0.2, i, 0.0);
    }

    glColor3f (_colorZ.redF(), _colorZ.greenF(), _colorZ.blueF());
    for( int i=_rangeZ.rangeBegin; i <= (int)_rangeZ.rangeEnd; i++ )
    {
        glVertex3f (0.0, 0.0, i);
        glVertex3f (0.0, -0.2, i);
    }

    glEnd ();

    glPushMatrix();

    glTranslatef(0, 0, 5);

    gluCylinder(gluNewQuadric(), 0.1, 0, 0.3, 16, 4);

    /*GLubyte Font[14]= {
        33,
        0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18
    };

    glBitmap(8,8,0,0,0,0,Font);*/

    glPopMatrix();

    //glPopMatrix();
}
