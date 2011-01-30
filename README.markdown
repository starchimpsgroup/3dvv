<u>Qt 3D Vector Viewer</u>
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

- <font color="green">Code:</font>

>- <font color="green">Supports Linux</font>
>- <font color="green">C++ (Qt), OpenGL</font>

- <font color="red">File / Script (XML) to represent objects (created by the user)</font>

>- <font color="red">Object has:</font>

>>- <font color="red">ObjectID or unique name</font>
>>- <font color="red">ObjectTyp:</font>

>>>- <font color="red">Point (to be shown as a cross)</font>
>>>- <font color="orange">Vector (for display with apex)</font>
>>>- <font color="red">Layer</font>
>>>- <font color="red">Line</font>
>>>- <font color="red">Angle</font>

>>- <font color="red">Coordinates:</font>

>>>- <font color="red">Point, only coordinates</font>
>>>- <font color="red">Vector, start and end point</font>

>>- <font color="red">Time parameters for film script</font>
>>- <font color="red">Delete object in the script</font>

- <font color="orange">View:</font>

>- <font color="orange">Coordinate axes (to infinity), perpendicular to each other</font>

>>- <font color="red">Not on every tick a number</font>

>- <font color="orange">Camera control (mouse, keyboard)</font>
>- <font color="red">Objects highlight temporarily, which are displayed newly (in color or otherwise)</font>
>- <font color="red">Object labeling (automatic), font same color as object</font>
>- <font color="red">Layer can be show (to infinity), semi-transparent</font>
>- <font color="red">Line can be adjust to infinity</font>
>- <font color="red">Display angels, between vectors (default, smaller angle)</font>

>>- <font color="red">Display angular size (degree / radian)</font>

>- <font color="red">Color mapping for objects (RGB / Hex) (default color, if not specify)</font>
>- <font color="red">Show coordinates (start, end, middle)</font>
>- <font color="red">Pause function</font>
>- **Optional:** <font color="red">Single step</font>

<font color="green">`*ready*`</font>
<font color="orange">`*work in progress*`</font>
<font color="red">`*untouched*`</font>
