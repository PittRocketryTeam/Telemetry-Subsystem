//#version 330 core
#version 300 es
precision highp float;

out vec4 color;

uniform sampler2D tex;

void main()
{
    color = vec4(1.0, 0.0, 1.0, 1.0);
}

