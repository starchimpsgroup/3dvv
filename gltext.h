/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#ifndef GLTEXT_H
#define GLTEXT_H

#include <QString>
#include "glcolor.h"
#include "glvector.h"
#include <qgl.h>
#include <QImage>
#include <QMap>

#define TEXTSIZE 25     //!< Size of the text
#define PIXEL 0.0078125 //!< Size of a pixel in the 3D view
#define SPACER 2        //!< Space between multiline text

//! The Text class.
/*!
    A static class to generate text textures and draw them in the 3D view.
    This class shows a text on a given poition and color, in the direction of two angles.
 */
class GLText : public QObject
{
    Q_OBJECT
public:
    //! Draw function of the GLText.
    /*!
        Draw the text on a position with the given angle.
        The angles are set global for all other texts.
        \param text Text to draw
        \param color Color of the text
        \param position Position of the text
        \param angleX First angle of the text
        \param angleY Second angle of the text
        \see GLColor
        \see GLVector
     */
    static void draw( QString text, GLColor color, GLVector position, float angleX, float angleY );

    //! Draw function of the GLText.
    /*!
        Draw the text on a position with the given angle.
        The text texture will be generated or a existent texture with the same color and text will be usesd.
        \param text Text to draw
        \param color Color of the text
        \param position Position of the text
        \see GLColor
        \see GLVector
     */
    static void draw( QString text, GLColor color, GLVector position );

    //! Sets angels for the rotation around the position
    /*!
        \param angleX First angle of the text
        \param angleY Second angle of the text
     */
    static void setAngels( float angleX, float angleY ){ _angleX = angleX; _angleY = angleY; }

    //! Returns the calculated height of the given text string.
    /*!
        \return Height of text
     */
    static float heightOfText(QString text);

private:
    //! Draw the text in the 3D view
    /*!
        Get the generated image and the position and draws the texture on a quad in the 3D view and rotate it by the given angles.
        \param image The generated texture and the id
        \param position The position of the text in the 3D view
        \param angleX First angle of the text
        \param angleY Second angle of the text
     */
    static void draw(QPair<QImage, GLuint> &image, GLVector &position, float angleX, float angleY);

    //! Generate image
    /*!
        Generates an image by the given text and color and saves it in a map of generated text textures.
        \param text Text to generate
        \param color Color to use
     */
    static void createImage(QString &text, GLColor &color);

    //! Create name
    /*!
        Generates a name vor the texture for the identification in the texture map.
        \param text Text to draw
        \param color Color to use
        \return Generated name of the texture
     */
    static QString createName(QString &text, GLColor &color);

    //! Initialise the map vor the generated textures
    /*!
        Create a empty map and return it for the for the initialisation of the map.
        \return Created empty map
     */
    static QMap<QString, QPair<QImage, GLuint> > initMap();

    //! Returns the index of the longest text part in a list
    /*!
        Get a list to check what text part is the longest and return the index of that part.
        \param list List of textparts
        \return Index of the longest textpart
     */
    static int longestPart( QStringList &list );

private:
    static QMap<QString, QPair<QImage, GLuint> > _imageMap; //!< Map of text textures
    static float _angleX; //!< First angle of the text
    static float _angleY; //!< Second angle of the text
};

#endif // GLTEXT_H
