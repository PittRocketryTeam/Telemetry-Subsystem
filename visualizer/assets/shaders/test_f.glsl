//#version 330 core
#version 300 es
precision highp float;
in vec2 uv;
in vec3 n;
out vec4 color;

void main()
{
    //float i = exp(dot(normalize(vec3(0,0,0) - vec3(3,2,3)), normalize(n))) / exp(1.0);
    color = vec4(1, 0.5, 0, 1.0);
}

