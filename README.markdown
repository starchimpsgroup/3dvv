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

- File / Script (XML) to represent objects (created by the user) `*work in progress*`

>- Object has: `*work in progress*`

>>- ObjectID or unique name `*work in progress*`
>>- ObjectTyp: `*work in progress*`

>>>- Point (to be shown as a cross) `*ready*`
>>>- Vector (for display with peak) `*ready*`
>>>- Plain `*ready*`
>>>- Line `*ready*`
>>>- Angle `*work in progress*`

>>- Coordinates: `*ready*`

>>>- Point, only coordinates `*ready*`
>>>- Vector, start and end point `*ready*`

>>- Time parameters for film script `*ready*`
>>- Delete object in the script `*ready*`

- View: `*work in progress*`

>- Coordinate axes (to infinity), perpendicular to each other `*work in progress*`

>>- Not on every tick a number `*ready*`

>- Camera control (mouse, keyboard) `*work in progress*`
>- Objects highlight temporarily, which are displayed newly (in color or otherwise) `*work in progress*`
>- Object labeling (automatic), font same color as object `*ready*`
>- Plain can be show (to infinity), semi-transparent `*work in progress*`
>- Line can be adjust to infinity `*work in progress*`
>- Display angels, between vectors (default, smaller angle) `*work in progress*`

>>- Display angular size (degree / radian) `*untouched*`

>- Color mapping for objects (RGB / Hex) (default color, if not specify) `*ready*`
>- Show coordinates (start, end, middle) `*ready*`
>- Pause function `*ready*`
>- **Optional:** Single step `*ready*`
