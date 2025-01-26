## CAP 5705 – Final Project

## Project Title: Texture and Normal Mapping

## PREREQUISITES:
YOU NEED TO HAVE GLEW AND GLFW LIBRARIES DOWNLOADED IN YOUR SYSTEM..

## RUNNING THE PROGRAM
For MAC and LINUX (C++ compiler of your chose (clang++ or g++)):
    Now you can simply run the make file, by typing the command make.
    If not you can simply type this command in you terminal once you are in our project folder.

    g++ ./*.cpp -o ./a.out -I./GL -I./GLFW -I./GLM -framework OpenGL -L./GLFW/lib -lglfw -L./GL/lib -lglew  

For WINDOWS:
    Simply type this command in you terminal once you cd to our project folder.

    g++ ./*.cpp -o ./a.out -I./GL -I./GLFW -I./GLM -L./GLFW/lib -lglfw -L./GL/lib -lglew 

## EXECUTING THE PROGRAM
Once you have run the above command, you should be able to see an a.out or a.exe file in the folder. 
Run that file to view the Window to see our scene: 

    ./a.out {FileName} {texture}

For file name you can pick any file in the obj folder, and for runAt you have to mention which type of mapping do you want or lighting you want.

For example:
    a.out crocodile.obj texture  (For texture mapping)
or 
    a.out crocodile.obj texturenormal (for normal mapping) When using normal mapping you can use n and m to turn normal mapping on and off, where N is to turn it on and M to turn it off.
or 
    a.out cube.obj phong/gouraud/flat (to see previous lighting effects)



You can also run the z Buffer code by doing,

    a.out cube.obj zbuffer

You can run any file that has the vertex normal given in it.

## TRANFORMATION OPERATION

In the running app, you tranform the objects:

Move Up      : Press W
Move Down    : Press S
Move Left    : Press A
Move Right   : Press D
Move Back    : Press Q
Move Forward : Press E

Scale Up = Press Up
Scale Down = Press Down 

Rotate = LEFT AND RIGHT ARROW

For Rotation along X axis : the Program expects the user to press X before pressing the LEFT Arrow and the RIGHT Arrow as input. 

For Rotation along Y axis : the Program expects the user to press Y before pressing the LEFT Arrow and the RIGHT Arrow as input. 

For Rotation along Z axis : the Program expects the user to press Z before pressing the LEFT Arrow and the RIGHT Arrow as input. 

For Rotation along X_Y axis : the Program expects the user to press F before pressing the LEFT Arrow and the RIGHT Arrow as input. 

For Rotation along X_Z axis : the Program expects the user to press G before pressing the LEFT Arrow and the RIGHT Arrow as input. 

For Rotation along Y_Z axis : the Program expects the user to press H before pressing the LEFT Arrow and the RIGHT Arrow as input. 


If you want to play algo with the fov(field of view), for perspective: 
 
You can press P to increase the angle
You can press O to decrease the angle

Press N to enable normal mapping
Press M to disable normal mapping

Press J, K, and L to switch which texture is rendered onto the model

## REFERENCES
1.	https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
2.	https://stackoverflow.com/questions/36441192/opengl-fragment-shaders-changing-a-fixed-color
3.	https://www.khronos.org/opengl/wiki/Uniform_(GLSL)
4.	https://www.khronos.org/opengl/wiki/Fragment_Shader#Outputs
5.	https://learnopengl.com/Getting-started/Shaders
6.	https://learnopengl.com/Advanced-OpenGL/Face-culling
7.	https://jsantell.com/model-view-projection/
8.	https://www.artec3d.com/3d-models/bearded-guy-hd
9.  https://sketchfab.com/3d-models/titanic-high-poly-obj-39455b6143d64b25ac2382d067be90ae
10. https://learnopengl.com/Advanced-OpenGL/Depth-testing
11. https://learnopengl.com/Getting-started/Textures
12. https://github.com/nothings/stb/blob/master/stb_image.h
