#version 330 core
in vec3 vColor;
in vec2 TexCoord;
in vec3 viewPos;
out vec4 FragColor;

const vec3 lightDir = normalize(vec3(0,0, 1));

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

uniform mat4 model; 

uniform int normMapToggle;
uniform int texCycle;

void main()
{

    vec3 xTangent = dFdx(viewPos);
    vec3 yTangent = dFdy(viewPos);
    vec3 faceNormal = normalize(cross(xTangent, yTangent));
    vec3 T = normalize(vec3(model * vec4(xTangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(yTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(faceNormal, 0.0)));

    mat3 TBN = mat3(T,B,N);

    vec3 normal = texture(texture2, TexCoord).rgb *2.0f - 1.0f;
    normal = normalize(TBN *normal);

    float lightCoef;
    //toggle norm-map on/off
    if (normMapToggle == 1) {
        lightCoef = dot(lightDir, normal);
    }
    else {
        lightCoef = dot(lightDir, faceNormal);
    }

    if (texCycle == 0) {
        FragColor = vec4(lightCoef * texture(texture1, TexCoord).rgb, 1.0);
    }
    else if (texCycle == 1) {
        FragColor = vec4(lightCoef * texture(texture3, TexCoord).rgb, 1.0);
    }
    else if (texCycle == 2) {
        FragColor = vec4(lightCoef * texture(texture4, TexCoord).rgb, 1.0);
    }
    else {
        FragColor = vec4(lightCoef * vec3(0.5, 0.5, 0.5), 1.0);
    }
}

