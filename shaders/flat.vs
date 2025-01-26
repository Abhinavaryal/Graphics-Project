#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 vColor;
out vec3 viewPos;

const vec3 pLight = vec3(-2.0f,15.0f,-3.0f);
const vec3 lColor = vec3(0.5f, 0.5f, 0.5f);
const float n = 0.5f;

//for modelview matrix that we created
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 
uniform mat4 modelViewProjection; 

void main()
{
   gl_Position = modelViewProjection * vec4(aPos, 1.0);
   viewPos = gl_Position.xyz;
   vColor = aColor;
}