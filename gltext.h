#ifndef GLTEXT_H
#define GLTEXT_H

#include <QString>
#include "glcolor.h"
#include "glvector.h"
#include <qgl.h>
#include <QImage>

#define TEXTSIZE 25
#define PIXEL 0.0078125

class GLText
{
public:
    static void draw( QString text, GLColor color, GLVector position, GLfloat angleX, GLfloat angleY )
    {
        glPushMatrix();

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

        glPopMatrix();
    }
};

#endif // GLTEXT_H
