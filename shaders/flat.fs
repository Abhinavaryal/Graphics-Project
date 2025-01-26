#version 330 core
in vec3 vColor;
in vec3 viewPos;
out vec4 FragColor;

const vec3 lightDir = normalize(vec3(-0.5, -0.5, 0.5));

void main()
{
    vec3 xTangent = dFdx(viewPos);
    vec3 yTangent = dFdy(viewPos);
    vec3 faceNormal = normalize(cross(xTangent, yTangent));

    float lightCoef = dot(lightDir, faceNormal);

    FragColor = vec4(lightCoef * vColor, 1.0);
}