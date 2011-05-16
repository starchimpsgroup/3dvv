#ifndef GLTEXT_H
#define GLTEXT_H

#include <QString>
#include "glcolor.h"
#include "glvector.h"
#include <qgl.h>
#include <QImage>
#include <QMap>

#define TEXTSIZE 25
#define PIXEL 0.0078125
#define SPACER 2

class GLText : public QObject
{
    Q_OBJECT
public:
    static void draw( QString text, GLColor color, GLVector position, float angleX, float angleY );
    static void draw( QString text, GLColor color, GLVector position );

    static void setAngels( float angleX, float angleY ){ _angleX = angleX; _angleY = angleY; }

    static float heightOfText(QString text);

private:
    static void draw(QPair<QImage, GLuint> &image, GLVector &position, float angleX, float angleY);

    static void createImage(QString &text, GLColor &color);

    static QString createName(QString &text, GLColor &color);

    static QMap<QString, QPair<QImage, GLuint> > initMap();

    static float initAngel(){ return 0.0f; }

    static int longestPart( QStringList &list );

private:
    static QMap<QString, QPair<QImage, GLuint> > _imageMap;
    static float _angleX;
    static float _angleY;
};

#endif // GLTEXT_H
