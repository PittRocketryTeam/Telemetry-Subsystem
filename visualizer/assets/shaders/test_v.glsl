#version 330 core

precision highp float;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 vertex_uv;

out vec3 n;
out vec2 uv;

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

void main()
{
    gl_Position = p * v * m * (vec4(position, 1));

    uv = vertex_uv;
    n = -vec3(m * vec4(normal,1));
}
