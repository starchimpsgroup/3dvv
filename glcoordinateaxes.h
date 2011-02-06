#ifndef GLCOORDINATEAXES_H
#define GLCOORDINATEAXES_H

#include <qgl.h>
#include <glcolor.h>

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
    void drawDistanceMarker();

    void setDefaultColors();

    void setColors( const GLColor &colorX,
                    const GLColor &colorY,
                    const GLColor &colorZ );

    void setRanges( const GLCoordinateAxes::Range &rangeX,
                    const GLCoordinateAxes::Range &rangeY,
                    const GLCoordinateAxes::Range &rangeZ);

private:
    Range _rangeX, _rangeY, _rangeZ;
    GLColor _colorX, _colorY, _colorZ;

};

#endif // GLCOORDINATEAXES_H
