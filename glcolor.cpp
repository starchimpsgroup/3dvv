/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "glcolor.h"
#include <QString>

GLColor::GLColor()
{
    _red   = 0.0f;
    _green = 0.0f;
    _blue  = 0.0f;
    _alpha = 1.0f;
}

GLColor::GLColor( float redF, float greenF, float blueF, float alphaF )
{
    _red   = redF;
    _green = greenF;
    _blue  = blueF;
    _alpha = alphaF;
}

GLColor::GLColor( int redI, int greenI, int blueI, int alphaI )
{
    _red   = redI   / 255.0;
    _green = greenI / 255.0;
    _blue  = blueI  / 255.0;
    _alpha = alphaI / 255.0;
}

GLColor::GLColor( QColor color )
{
    _red   = color.redF();
    _green = color.greenF();
    _blue  = color.blueF();
    _alpha = color.alphaF();
}

const QColor GLColor::qcolor()
{
    return QColor(redDez(), greenDez(), blueDez(), alphaDez());
}
