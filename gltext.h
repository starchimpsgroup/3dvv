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

class GLText : public QObject
{
    Q_OBJECT
private:
    static QMap<QString, QImage> initMap();
    static QMap<QString, QImage> _imageMap;


public:
    static void draw( QString text, GLColor color, GLVector position, GLfloat angleX, GLfloat angleY );

private:
    static void draw(QImage image, GLVector position, GLfloat angleX, GLfloat angleY);

    static void createImage(QString text, GLColor color);

    static QString createName(QString text, GLColor color);
};

#endif // GLTEXT_H
