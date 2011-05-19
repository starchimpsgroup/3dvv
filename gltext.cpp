#include "gltext.h"

float GLText::_angleX = 0.0;
float GLText::_angleY = 0.0;
QMap<QString, QPair<QImage, GLuint> > GLText::_imageMap(GLText::initMap());

QMap<QString, QPair<QImage, GLuint> > GLText::initMap()
{
    QMap<QString, QPair<QImage, GLuint> > temp;
    return temp;
}

void GLText::draw( QString text, GLColor color, GLVector position )
{
    if(!text.isEmpty())
    {
        if(!_imageMap.contains(createName(text, color)))
        {
            createImage(text, color);
        }

        draw(_imageMap[createName(text, color)], position, _angleX, _angleY);
    }
}

void GLText::draw( QString text, GLColor color, GLVector position, float angleX, float angleY )
{
    _angleX = angleX;
    _angleY = angleY;

    draw(text, color, position);
}

void GLText::draw(QPair<QImage, GLuint> &image, GLVector &position, float angleX, float angleY)
{
    glPushMatrix();

    glTranslatef(position.x(), position.y(), position.z());
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);	       // Aktiviert Texture Mapping

    glBindTexture(GL_TEXTURE_2D, image.second);

    // Alpha Test löscht pixel
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0);

    // Blend macht durchsichtig
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(1.0, 1.0, 1.0);
    glBegin( GL_QUADS );
    glTexCoord2d(0.0,0.0); glVertex2d(-(image.first.width()*PIXEL/2.0),-(image.first.height()*PIXEL/2.0));
    glTexCoord2d(1.0,0.0); glVertex2d(  image.first.width()*PIXEL/2.0 ,-(image.first.height()*PIXEL/2.0));
    glTexCoord2d(1.0,1.0); glVertex2d(  image.first.width()*PIXEL/2.0 ,  image.first.height()*PIXEL/2.0 );
    glTexCoord2d(0.0,1.0); glVertex2d(-(image.first.width()*PIXEL/2.0),  image.first.height()*PIXEL/2.0 );
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

int GLText::longestPart( QStringList &list )
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

void GLText::createImage(QString &text, GLColor &color)
{
    int width, height, bracketsWidth = 0, bracketsHeight = 0;
    QString textInput = text;
    QFont font;

    if(textInput.indexOf("\n") != -1 && textInput.startsWith("(") && textInput.endsWith(")"))
    {
        textInput = textInput.mid(1,textInput.size()-2);
        bracketsHeight = (TEXTSIZE + SPACER) * (textInput.count("\n") + 1);
        bracketsWidth = 20;
    }

    QStringList stringList = textInput.split("\n");
    font.setPointSize(TEXTSIZE);

    width  = QFontMetrics(font).width(stringList.at(longestPart(stringList))) + bracketsWidth*2;
    height = (TEXTSIZE + SPACER) * stringList.size();

    QImage picture(width, height, QImage::Format_ARGB32);
    QPainter paint(&picture);

    for (int i = 0; i < picture.height() * picture.width() * 4; i++) // 4 für RGBA
        picture.bits()[i] = 0;

    paint.setPen(QColor(color.redDez(), color.greenDez(), color.blueDez()));//, color.alphaDez()));

    if(bracketsWidth > 0)
    {
        QPen pen = paint.pen();
        pen.setWidth(3);
        paint.setPen(pen);
        int part = 5760/4;

        paint.drawArc(QRectF(4, 0, bracketsWidth, bracketsHeight), part, 2*part);
        paint.drawArc(QRectF(width-bracketsWidth-4, 0, bracketsWidth, bracketsHeight), -part, 2*part);
    }

    paint.setFont(font);
    for(int i = 0; i < stringList.size(); i++)
    {
        paint.drawText(bracketsWidth,TEXTSIZE*(i+1)+SPACER*i,stringList.at(i));
    }
    paint.end();
    //picture.save(text + ".png", "PNG");

    QImage glPicture = QGLWidget::convertToGLFormat(picture);
    GLuint textureName;

    glGenTextures(1, &textureName);
    glBindTexture(GL_TEXTURE_2D, textureName);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    // wrap textur on borders
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glPicture.width(), glPicture.height(), 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, glPicture.constBits());

    _imageMap.insert(createName(text, color), qMakePair(glPicture, textureName));
}

QString GLText::createName(QString &text, GLColor &color)
{
    return text + "#" + QString::number(color.redDez())
                + "#" + QString::number(color.greenDez())
                + "#" + QString::number(color.blueDez())
                + "#" + QString::number(color.alphaDez());
}

float GLText::heightOfText(QString text)
{
    return (TEXTSIZE + SPACER) * (text.count("\n") + 1) * PIXEL;
}
