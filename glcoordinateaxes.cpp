#include "glcoordinateaxes.h"
#include <QFile>
#include <QDataStream>
#include <QImage>
#include <QPicture>

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

    glColor3f (_colorX.redF(), _colorX.greenF(), _colorX.blueF());
    drawCylinder(GLVector(_rangeX.rangeBegin + CYLINDERHEIGHT, 0.0, 0.0), v_Y, 270.0);
    drawCylinder(GLVector(_rangeX.rangeEnd   - CYLINDERHEIGHT, 0.0, 0.0), v_Y, 90.0);

    glColor3f (_colorY.redF(), _colorY.greenF(), _colorY.blueF());
    drawCylinder(GLVector(0.0, _rangeY.rangeBegin + CYLINDERHEIGHT, 0.0), v_X, 90.0);
    drawCylinder(GLVector(0.0, _rangeY.rangeEnd   - CYLINDERHEIGHT, 0.0), v_X, 270.0);

    glColor3f (_colorZ.redF(), _colorZ.greenF(), _colorZ.blueF());
    drawCylinder(GLVector(0.0, 0.0, _rangeZ.rangeBegin + CYLINDERHEIGHT), v_Y, 180.0);
    drawCylinder(GLVector(0.0, 0.0, _rangeZ.rangeEnd   - CYLINDERHEIGHT), v_Y, 0.0);

    // Test

    //glPushMatrix();

    glEnable(GL_TEXTURE_2D);	       // Aktiviert Texture Mapping

    int width, height;
    //QByteArray data;

    // texture data
    width  = 256;
    height = 256;
    /*char b[width*height*3];

    for(int i = 0; i < width*height*3; i++)
    {
        b[i] = 150;
    }*/

    /*QFile file("/home/cernst/Qt3DVectorViewer-build-desktop/Alphatest_Tex.png");
    if (!file.open(QIODevice::ReadOnly))
        return;

    data = file.readAll();*/

    QImage pic(width, height, QImage::Format_ARGB32);
    QPainter paint(&pic);

    paint.begin(&pic);

    for (int i = 0; i < pic.height() * pic.width() * 4; i++) // 4 für RGBA
        pic.bits()[i] = 0;

    QFont font = paint.font();
    font.setPixelSize(100);

    paint.setPen(Qt::blue);
    //paint.setBrush(Qt::blue);
    paint.setFont(font);
    paint.drawText(0,100,"test");
    //paint.drawRect(0,0,20,20);
    paint.end();
    pic.save("drawing.png", "PNG");

    QImage t = QGLWidget::convertToGLFormat(pic);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    // http://wiki.delphigl.com/index.php/glAlphaFunc
    // http://www.sorgonet.com/games/fogshadow/
    glAlphaFunc(GL_GREATER, 0.0);
    //glBlendFunc(GL_DST_COLOR, GL_ZERO);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pic.width(), pic.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, /*b*/ /*data.data()*/ t.constBits());

    glBegin( GL_QUADS );
    glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
    glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
    glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
    glEnd();

    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

}

void GLCoordinateAxes::drawDistanceMarker()
{
    glBegin (GL_LINES);

    glColor3f (_colorX.redF(), _colorX.greenF(), _colorX.blueF());
    for( int i=_rangeX.rangeBegin+CYLINDERHEIGHT; i <= (int)_rangeX.rangeEnd-CYLINDERHEIGHT; i++ )
    {
        if( i != 0)
        {
            glVertex3f (i, 0.0, 0.0);
            glVertex3f (i, -0.2, 0.0);
        }
    }

    glColor3f (_colorY.redF(), _colorY.greenF(), _colorY.blueF());
    for( int i=_rangeY.rangeBegin+CYLINDERHEIGHT; i <= (int)_rangeY.rangeEnd-CYLINDERHEIGHT; i++ )
    {
        if( i != 0)
        {
            glVertex3f (0.0, i, 0.0);
            glVertex3f (-0.2, i, 0.0);
        }
    }

    glColor3f (_colorZ.redF(), _colorZ.greenF(), _colorZ.blueF());
    for( int i=_rangeZ.rangeBegin+CYLINDERHEIGHT; i <= (int)_rangeZ.rangeEnd-CYLINDERHEIGHT; i++ )
    {
        if( i != 0)
        {
            glVertex3f (0.0, 0.0, i);
            glVertex3f (0.0, -0.2, i);
        }
    }

    glEnd ();
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
