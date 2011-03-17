#include "gltext.h"

QMap<QString, QImage> GLText::initMap()
{
    QMap<QString, QImage> temp;
    return temp;
}

QMap<QString, QImage> GLText::_imageMap(GLText::initMap());

void GLText::draw( QString text, GLColor color, GLVector position, GLfloat angleX, GLfloat angleY )
{
    if(_imageMap.contains(createName(text, color)))
    {
        draw(_imageMap[createName(text, color)], position, angleX, angleY);
    }
    else
    {
        createImage(text, color);
        draw(_imageMap[createName(text, color)], position, angleX, angleY);
    }

    /*glPushMatrix();

    glTranslatef(position.x(), position.y(), position.z());
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);

    QFont font;
    font.setPointSize(TEXTSIZE);

    int width, height;

    width  = QFontMetrics(font).width(text);
    height = TEXTSIZE;

    QImage picture(width, height, QImage::Format_ARGB32);
    QPainter paint(&picture);

    for (int i = 0; i < picture.height() * picture.width() * 4; i++) // 4 für RGBA
        picture.bits()[i] = 0;

    paint.setPen(QColor(color.redDez(), color.greenDez(), color.blueDez(), color.alphaDez()));
    paint.setFont(font);
    paint.drawText(0,TEXTSIZE,text);
    paint.end();
    picture.save("drawing.png", "PNG");

    QImage glPicture = QGLWidget::convertToGLFormat(picture);

    glEnable(GL_TEXTURE_2D);	       // Aktiviert Texture Mapping

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    // wrap textur on borders
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

    // Alpha Test löscht pixel
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0);

    // Blend macht durchsichtig
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, picture.width(), picture.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, glPicture.constBits());

    glColor3f(1.0, 1.0, 1.0);
    glBegin( GL_QUADS );
    glTexCoord2d(0.0,0.0); glVertex2d(-(width*PIXEL/2.0),-(height*PIXEL/2.0));
    glTexCoord2d(1.0,0.0); glVertex2d(  width*PIXEL/2.0 ,-(height*PIXEL/2.0));
    glTexCoord2d(1.0,1.0); glVertex2d(  width*PIXEL/2.0 ,  height*PIXEL/2.0 );
    glTexCoord2d(0.0,1.0); glVertex2d(-(width*PIXEL/2.0),  height*PIXEL/2.0 );
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();*/
}

void GLText::draw(QImage image, GLVector position, GLfloat angleX, GLfloat angleY)
{
    glPushMatrix();

    glTranslatef(position.x(), position.y(), position.z());
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);	       // Aktiviert Texture Mapping

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    // wrap textur on borders
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

    // Alpha Test löscht pixel
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0);

    // Blend macht durchsichtig
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image.constBits());

    glColor3f(1.0, 1.0, 1.0);
    glBegin( GL_QUADS );
    glTexCoord2d(0.0,0.0); glVertex2d(-(image.width()*PIXEL/2.0),-(image.height()*PIXEL/2.0));
    glTexCoord2d(1.0,0.0); glVertex2d(  image.width()*PIXEL/2.0 ,-(image.height()*PIXEL/2.0));
    glTexCoord2d(1.0,1.0); glVertex2d(  image.width()*PIXEL/2.0 ,  image.height()*PIXEL/2.0 );
    glTexCoord2d(0.0,1.0); glVertex2d(-(image.width()*PIXEL/2.0),  image.height()*PIXEL/2.0 );
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void GLText::createImage(QString text, GLColor color)
{
    QFont font;
    font.setPointSize(TEXTSIZE);

    int width, height;

    width  = QFontMetrics(font).width(text);
    height = TEXTSIZE;

    QImage picture(width, height, QImage::Format_ARGB32);
    QPainter paint(&picture);

    for (int i = 0; i < picture.height() * picture.width() * 4; i++) // 4 für RGBA
        picture.bits()[i] = 0;

    paint.setPen(QColor(color.redDez(), color.greenDez(), color.blueDez(), color.alphaDez()));
    paint.setFont(font);
    paint.drawText(0,TEXTSIZE,text);
    paint.end();
    //picture.save("drawing.png", "PNG");

    QImage glPicture = QGLWidget::convertToGLFormat(picture);

    GLText::_imageMap.insert(createName(text, color), glPicture);
}

QString GLText::createName(QString text, GLColor color)
{
    return text + "#" + QString::number(color.redF())
                + "#" + QString::number(color.greenF())
                + "#" + QString::number(color.blueF())
                + "#" + QString::number(color.alpaF());
}
