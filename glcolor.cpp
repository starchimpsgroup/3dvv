/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "glcolor.h"
#include <QString>

GLColor::GLColor()
{
    _red   = 1.0f;
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
    _red   = color.red()   / 255.0;
    _green = color.green() / 255.0;
    _blue  = color.blue()  / 255.0;
    _alpha = color.alpha() / 255.0;
}

const QColor GLColor::qcolor()
{
    return QColor(redDez(), greenDez(), blueDez(), alphaDez());
}
