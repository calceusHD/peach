

#version 300 es

layout(location = 0) in vec2 pos;
layout(location = 1) in vec4 aux;
out highp vec2 uv;
flat out highp float width;
uniform highp mat4 mvp;
void main(void)
{
    gl_Position = mvp * vec4(pos, 0.0, 1.0);
    uv = aux.xy;
    width = aux.z;
}
