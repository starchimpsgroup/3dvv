/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include <QString>
#include "glcolor.h"
#include <QDomElement>

#ifndef GLOBJECT_H
#define GLOBJECT_H

//! The Object class.
/*!
    This is the abstarct class for the mathematic objects.
    The objects for the 3D view must implement this class to work.
 */
class GLObject
{
public:
    //! The different types of objects.
    /*!
        This enum contains the different object, they are created with tihs class.
        This must be expanded if there will be more objects created with this class.
     */
    typedef enum ObjectType
    {
        ANGLE_OBJECT,
        DELETE_OBJECT,
        LINE_OBJECT,
        PLANE_OBJECT,
        POINT_OBJECT,
        VECTOR_OBJECT
    }
    ObjectType;

    //! Constructor of the GLObject class.
    /*!
        Initialize the object with given parameters.
        \param type Type of the object
        \param color Color for drawing the object
        \param objectID Unique identifier for the object
        \param time Time to draw the object in msec (milliseconds)
        \see ObjectType
        \see GLColor
     */
    GLObject( ObjectType type, GLColor color = GLColor(), QString objectID = "", int time = 0 );

    //! Copy constructor of the GLObject class.
    GLObject( const GLObject &o );

    //! Set ID.
    /*!
        Set the unique identifier for the object.
        \param objectID Unique identifier for the object
     */
    void setID       ( QString objectID );

    //! Set color.
    /*!
        Set the color for drawing the object.
        \param color Color for drawing the object
        \see GLColor
     */
    void setColor    ( GLColor color    );

    //! Set color.
    /*!
        Set the color for drawing the object.
        \param redF Red part of the color
        \param greenF Green part of the color
        \param blueF Blue part of the color
        \param alphaF Alpha part of the color
        \see GLColor
     */
    void setColor    ( float redF, float greenF, float blueF, float alphaF = 1.0f );

    //! Set time.
    /*!
        Set the time to draw the object in msec (milliseconds).
        \param time Time to draw the object in msec (milliseconds)
     */
    void setTime     ( int time         );

    //! Set values.
    /*!
        Set the object id, the color and the time at the same time.
        \param objectID Unique identifier for the object
        \param color Color for drawing the object
        \param time Time to draw the object in msec (milliseconds)
        \see GLColor
     */
    void setValues   ( QString objectID, GLColor color = GLColor(), int time = 0 );

    //! Set draw.
    /*!
        Set the draw falue, to allow or forbid the drawing of the object.
        This function is used by the delete object.
        \param draw Value to allow or forbid the drawing of the object
     */
    void setDraw     ( bool draw        );

    //! Set highlight.
    /*!
        Set the highlight falue, to allow or forbid the highlighting of the object.
        This function is used by the main window.
        \param highlight Value to allow or forbid the highlighting of the object
     */
    void setHighlight( bool highlight   );

    //! Return object id.
    /*!
        \return Unique identifier for the object
     */
    QString    id()   const{ return _objectID; }

    //! Return color.
    /*!
        \return Color for drawing the object
     */
    GLColor    color()const{ return _color;    }

    //! Return time.
    /*!
        \return Time to draw the object in msec (milliseconds)
     */
    int        time() const{ return _time;     }

    //! Return type.
    /*!
        \return Type of the object
        \see ObjectType
     */
    ObjectType type() const{ return _type;     }

    //! Return drawing.
    /*!
        \return Drawing value, to allow or forbid the drawing of the object.
     */
    bool isDrawing()  const{ return _draw;     }

    //! Draw.
    /*!
        Draws the object if the drawing value is true.
        This function is calling the glObject function.
        \see isDrawing
        \see glObject
     */
    void draw();

    //! Draw object id.
    /*!
        Draws the object id text if the drawing value is true.
        This function is calling the glObjectId function.
        \see isDrawing
        \see glObjectId
     */
    void drawObjectId();

    //! Draw coordinate.
    /*!
        Draws the object coordinate text if the drawing value is true.
        This function is calling the glCoordinate function.
        \see isDrawing
        \see glCoordinate
     */
    void drawCoordinate();

    //! Draw vector.
    /*!
        Draws the object vector text if the drawing value is true.
        This function is calling the glVector function.
        \see isDrawing
        \see glVector
     */
    void drawVector();

    //! Return highlight color.
    /*!
        \return Color for drawing the object, if higlighting is active.
        \see GLColor
     */
    static GLColor highlightColor(){ return _highlightColor; }

    //! Set highlight color.
    /*!
        Set the highlight color for drawing the object, if higlighting is active.
        \param color Color for drawing the object, if higlighting is active.
        \see GLColor
     */
    static void setHighlightColor(GLColor color){ _highlightColor = color; }

protected:
    //! Draw object.
    /*!
        This function must be implemeneted to draw the object in the 3D view.
        The function is called by draw.
        \see draw
     */
    virtual void glObject() = 0;

    //! Draw object id.
    /*!
        This function can be implemeneted to draw the object id text in the 3D view.
        The function is called by drawObjectId.
        \see drawObjectId
     */
    virtual void glObjectId(){}

    //! Draw coordinate.
    /*!
        This function can be implemeneted to draw the object coordinate text in the 3D view.
        The function is called by drawCoordinate.
        \see drawCoordinate
     */
    virtual void glCoordinate(){}

    //! Draw vector.
    /*!
        This function can be implemeneted to draw the object vector text in the 3D view.
        The function is called by drawVector.
        \see drawVector
     */
    virtual void glVector(){}

    //! Return used color.
    /*!
        The color is the highlight color or the normal object color.
        \return Color that is used to draw the object.
     */
    GLColor usedColor();

protected:
    QString    _objectID; //!< Object id
    GLColor    _color;    //!< Object color \see GLColor
    int        _time;     //!< Object time

private:
    bool       _draw;     //!< Draw falue
    ObjectType _type;     //!< Object type \see ObjectType

    bool           _highlight;       //!< Highlight value
    static GLColor _highlightColor;  //!< Highlight color \see GLColor
};

#endif // GLOBJECT_H
