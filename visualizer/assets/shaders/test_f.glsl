#version 330 core

in vec2 uv;
in vec3 n;
out vec4 color;

void main()
{
    float i = exp(dot(normalize(vec3(0,0,0) - vec3(3,2,3)), normalize(n))) / exp(1.0);
    color = vec4(i, i, i + 0.05, 1.0);
}

