/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLCOLOR_H
#define GLCOLOR_H

#include <QColor>

//! The Color class.
/*!
    This class contains the values of a color.
 */
class GLColor
{
public:
    //! Constructor of the GLColor class without parameters.
    /*!
        Initialize with the standard color black.
     */
    GLColor();

    //! Constructor of the GLColor class with color parameters.
    /*!
        Initialize with the input colors and alpha in float.
        Input range 0.0f to 1.0f.
        \param redF color
        \param greenF color
        \param blueF color
        \param alphaF value
     */
    GLColor( float redF, float greenF, float blueF, float alphaF = 1.0f );

    //! Constructor of the GLColor class with color parameters.
    /*!
        Initialize with the input colors and alpha in integer.
        Input range 0 to 255.
        \param redI color
        \param greenI color
        \param blueI color
        \param alphaI value
     */
    GLColor( int redI, int greenI, int blueI, int alphaI = 255 );

    //! Constructor of the GLColor class with QColor parameter.
    /*!
        Initialize with colors and alpha in QColor.
        Input range 0 to 255.
        \param color QColor
     */
    GLColor( QColor color );

    //! Return red color of the color.
    /*!
        \see _red
        \return red color float
     */
    float redF()  { return _red; }

    //! Return green color of the color.
    /*!
        \see _green
        \return green color float
     */
    float greenF(){ return _green; }

    //! Return blue color of the color.
    /*!
        \see _blue
        \return blue color float
     */
    float blueF() { return _blue; }

    //! Return alpha value of the color.
    /*!
        \see _alpha
        \return alpha value float
     */
    float alphaF() { return _alpha; }

    //! Return red color of the color.
    /*!
        \see _red
        \return red color decimal
     */
    int redDez()  { return _red   * 255.0; }

    //! Return green color of the color.
    /*!
        \see _green
        \return green color decimal
     */
    int greenDez(){ return _green * 255.0; }

    //! Return blue color of the color.
    /*!
        \see _blue
        \return blue color decimal
     */
    int blueDez() { return _blue  * 255.0; }

    //! Return alpha value of the color.
    /*!
        \see _alpha
        \return alpha value decimal
     */
    int alphaDez(){ return _alpha * 255.0; }

    //! Set the colors and standard alpha in float.
    /*!
        \param redF color
        \param greenF color
        \param blueF color
        \param alphaF value
        \see _red
        \see _green
        \see _blue
        \see _alpha
     */
    void setColorsF(float redF, float greenF, float blueF, float alphaF = 1.0f){_red   = redF;
                                                                                _green = greenF;
                                                                                _blue  = blueF;
                                                                                _alpha = alphaF;}
    //! Set red color in float.
    /*!
        \param redF color
        \see _red
     */
    void setRedF  (float redF)  { _red   = redF;   }

    //! Set green color in float.
    /*!
        \param greenF color
        \see _green
     */
    void setGreenF(float greenF){ _green = greenF; }

    //! Set blue color in float.
    /*!
        \param blueF color
        \see _blue
     */
    void setBlueF (float blueF) { _blue  = blueF;  }

    //! Set alpha color in float.
    /*!
        \param alphaF color
        \see _alpha
     */
    void setAlphaF(float alphaF){ _alpha = alphaF; }

    //! Convert glcolor to qcolor
    /*!
        \return converted glcolor
     */
    const QColor qcolor();

    //! Transparenci status of the color
    /*!
        \return transparenci status
        \see _alpha
     */
    bool isTransparent(){ return _alpha != 1.0f; }

private:
    float _red;   //!< Red Color
    float _green; //!< Green Color
    float _blue;  //!< Blue Color
    float _alpha; //!< Alpha Value
};

#endif // GLCOLOR_H
