# GLUTSprong
GLUTSprong is a Pong-style game to test a way of doing 2D collissions. The underlying framework for collissions is intended to be easily extensible and new objects are added by implementing the abstract CollissionObject2D class and then adding the instances it to the list of pointers to collission objects and calling the appropriate update routines. How this is done should be clear from GLUTSprong.cpp.

![Game image.](https://raw.githubusercontent.com/mlaang/GLUTSprong/master/Output.png)

# Compiling
You will need to install GLUT and OpenGL and to link them.  
