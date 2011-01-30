#ifndef GLCOORDINATEAXES_H
#define GLCOORDINATEAXES_H

#include <qgl.h>

class GLCoordinateAxes
{
private:
    struct range
    {
     float rangeBegin, rangeEnd;
    };

    struct color
    {
     float red, green, blue;
    };

public:
    typedef struct range Range;
    typedef struct color Color;

    GLCoordinateAxes();

    GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                      const GLCoordinateAxes::Range &rangeY,
                      const GLCoordinateAxes::Range &rangeZ );

    GLCoordinateAxes( const GLCoordinateAxes::Range &rangeX,
                      const GLCoordinateAxes::Range &rangeY,
                      const GLCoordinateAxes::Range &rangeZ,
                      const GLCoordinateAxes::Color &colorX,
                      const GLCoordinateAxes::Color &colorY,
                      const GLCoordinateAxes::Color &colorZ );

    void draw();
    void drawDistanceMarker();

    void setDefaultColors();

    void setColors( const GLCoordinateAxes::Color &colorX,
                    const GLCoordinateAxes::Color &colorY,
                    const GLCoordinateAxes::Color &colorZ );

    void setRanges( const GLCoordinateAxes::Range &rangeX,
                    const GLCoordinateAxes::Range &rangeY,
                    const GLCoordinateAxes::Range &rangeZ);

private:
    Range _rangeX, _rangeY, _rangeZ;
    Color _colorX, _colorY, _colorZ;

};

#endif // GLCOORDINATEAXES_H
