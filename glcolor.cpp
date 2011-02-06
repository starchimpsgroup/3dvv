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

GLColor::GLColor()
{
    _red   = 0.0;
    _green = 0.0;
    _blue  = 0.0;
    _alpha = 1.0;
}

GLColor::GLColor( float redF, float greenF, float blueF )
{
    _red   = redF;
    _green = greenF;
    _blue  = blueF;
    _alpha = 1.0;
}

GLColor::GLColor( float redF, float greenF, float blueF, float alphaF )
{
    _red   = redF;
    _green = greenF;
    _blue  = blueF;
    _alpha = alphaF;
}
