#include "gltext.h"

float GLText::_angleX = GLText::initAngel();
float GLText::_angleY = GLText::initAngel();
QMap<QString, QImage> GLText::_imageMap(GLText::initMap());

QMap<QString, QImage> GLText::initMap()
{
    QMap<QString, QImage> temp;
    return temp;
}

void GLText::draw( QString text, GLColor color, GLVector position )
{
    if(_imageMap.contains(createName(text, color)))
    {
        draw(_imageMap[createName(text, color)], position, _angleX, _angleY);
    }
    else
    {
        createImage(text, color);
        draw(_imageMap[createName(text, color)], position, _angleX, _angleY);
    }
}

void GLText::draw( QString text, GLColor color, GLVector position, float angleX, float angleY )
{
    _angleX = angleX;
    _angleY = angleY;

    draw(text, color, position);
}

void GLText::draw(QImage image, GLVector position, float angleX, float angleY)
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

int GLText::longestPart( QStringList list )
{
    int longest = -1;

    if(list.size() > 1)
    {
        longest = 0;
        for(int i = 1; i < list.size(); i++)
        {
            if((QString)(list.at(i)).size() > (QString)(list.at(longest)).size())
                longest = i;
        }
    }
    else if(list.size() > 0)
    {
        return 0;
    }

    return longest;
}

void GLText::createImage(QString text, GLColor color)
{
    QFont font;
    font.setPointSize(TEXTSIZE);

    int width, height;
    QStringList stringList = text.split("\n");

    width  = QFontMetrics(font).width(stringList.at(longestPart(stringList)));
    height = TEXTSIZE * stringList.size() + SPACER * stringList.size();

    QImage picture(width, height, QImage::Format_ARGB32);
    QPainter paint(&picture);

    for (int i = 0; i < picture.height() * picture.width() * 4; i++) // 4 für RGBA
        picture.bits()[i] = 0;

    paint.setPen(QColor(color.redDez(), color.greenDez(), color.blueDez(), color.alphaDez()));
    paint.setFont(font);
    for(int i = 0; i < stringList.size(); i++)
    {
        paint.drawText(0,TEXTSIZE*(i+1)+SPACER*i,stringList.at(i));
    }
    paint.end();
    picture.save("drawing.png", "PNG");

    QImage glPicture = QGLWidget::convertToGLFormat(picture);

    _imageMap.insert(createName(text, color), glPicture);
}

QString GLText::createName(QString text, GLColor color)
{
    return text + "#" + QString::number(color.redF())
                + "#" + QString::number(color.greenF())
                + "#" + QString::number(color.blueF())
                + "#" + QString::number(color.alpaF());
}
