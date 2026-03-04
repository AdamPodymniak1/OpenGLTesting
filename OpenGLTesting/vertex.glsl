#version 400

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in mat4 transformMatrix;

out vec3 fCol;

void main()
{
    fCol = aCol;
    vec4 v = vec4(aPos, 1.0);
    gl_Position = transformMatrix * v;
}