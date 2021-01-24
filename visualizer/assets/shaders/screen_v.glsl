//#version 330 core
#version 300 es
precision highp float;

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 uv;

out vec2 tc;

void main()
{
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
    tc = uv;
}