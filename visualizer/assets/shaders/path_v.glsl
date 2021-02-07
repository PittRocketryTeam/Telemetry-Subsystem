//#version 330 core
#version 300 es

precision highp float;

layout(location = 0) in vec3 position;

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

void main()
{
    gl_Position = p * v * m * (vec4(position, 1));
}
