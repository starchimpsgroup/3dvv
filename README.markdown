Qt 3D Vector Viewer
==========================
Project title:
--------------
Presentation program of vectors in 3D

Project outline:
----------------
The development of a program, which displays objects of the vector analysis step by step. The description of the steps and objects should be saved in XML files.

Project background:
-------------------
The program which will be produced by us, is intended to bring the vector analysis  in math exercises or lectures the vector analysis graphically closer to the students.

Project description:
--------------------
This project is implemented with the programming language C + + and OpenGL, keeping in mind that the program should run on Linux.  Objects will be read from one, by the user created XML script file and will be presented three-dimensional in a window.  An object has a unique object ID. You can choose between the following types of objects: point, vector, layer, line and angle.

A Cartesian coordinate system is placed in this window.  In the window it should be possible to the move the angle and the viewer position. The objects must be highlighted at initial publication and additionally it should be possible to show a layer. It will be possible to show angles between vector-objects. The script created by the user will be processed attribute controlled, to represent objects one after another.

*Components: Version 1.0*
-----------------------------

- Code: `*ready*`

>- Supports Linux `*ready*`
>- C++ (Qt), OpenGL `*ready*`

- File / Script (XML) to represent objects (created by the user) `*untouched*`

>- Object has: `*work in progress*`

>>- ObjectID or unique name `*work in progress*`
>>- ObjectTyp: `*work in progress*`

>>>- Point (to be shown as a cross) `*untouched*`
>>>- Vector (for display with apex) `*ready*`
>>>- Layer `*untouched*`
>>>- Line `*untouched*`
>>>- Angle `*untouched*`

>>- Coordinates: `*untouched*`

>>>- Point, only coordinates `*untouched*`
>>>- Vector, start and end point `*ready*`

>>- Time parameters for film script `*ready*`
>>- Delete object in the script `*untouched*`

- View: `*work in progress*`

>- Coordinate axes (to infinity), perpendicular to each other `*work in progress*`

>>- Not on every tick a number `*untouched*`

>- Camera control (mouse, keyboard) `*work in progress*`
>- Objects highlight temporarily, which are displayed newly (in color or otherwise) `*untouched*`
>- Object labeling (automatic), font same color as object `*untouched*`
>- Layer can be show (to infinity), semi-transparent `*untouched*`
>- Line can be adjust to infinity `*untouched*`
>- Display angels, between vectors (default, smaller angle) `*untouched*`

>>- Display angular size (degree / radian) `*untouched*`

>- Color mapping for objects (RGB / Hex) (default color, if not specify) `*work in progress*`
>- Show coordinates (start, end, middle) `*untouched*`
>- Pause function `*untouched*`
>- **Optional:** Single step `*untouched*`
