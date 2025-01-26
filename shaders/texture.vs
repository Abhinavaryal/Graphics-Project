#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

//for modelview matrix that we created
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 
uniform mat4 modelViewProjection; 
uniform int yn;


void main()
{
    gl_Position = modelViewProjection * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;

}