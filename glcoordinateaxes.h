#ifndef GLCOORDINATEAXES_H
#define GLCOORDINATEAXES_H

#include <qgl.h>
#include <glcolor.h>
#include "glvector.h"

#define CYLINDERHEIGHT 0.3

class GLCoordinateAxes
{
private:
    struct range
    {
     float rangeBegin, rangeEnd;
    };

public:
    typedef struct range Range;

    GLCoordinateAxes();

    GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                      const GLCoordinateAxes::Range &rangeY,
                      const GLCoordinateAxes::Range &rangeZ );

    GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                      const GLCoordinateAxes::Range &rangeY,
                      const GLCoordinateAxes::Range &rangeZ,
                      const GLColor &colorX,
                      const GLColor &colorY,
                      const GLColor &colorZ );

    void draw();

    void setDefaultColors();

    void setColors( const GLColor &colorX,
                    const GLColor &colorY,
                    const GLColor &colorZ );

    void setRanges( const GLCoordinateAxes::Range &rangeX,
                    const GLCoordinateAxes::Range &rangeY,
                    const GLCoordinateAxes::Range &rangeZ);

private:
    void drawCylinder( const GLVector &point, const GLVector &around, GLfloat angel );
    void drawDistanceMarker();

private:
    Range _rangeX, _rangeY, _rangeZ;
    GLColor _colorX, _colorY, _colorZ;

};

#endif // GLCOORDINATEAXES_H
