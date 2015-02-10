

#version 300 es

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in float widthIn;
layout(location = 3) in vec2 cutoffIn;
layout(location = 4) in float lengthIn;
out highp vec2 uv;


out highp vec2 cutoff;
flat out highp float length;
flat out highp float width;
uniform highp mat4 mvp;
void main(void)
{
    gl_Position = mvp * vec4(pos, 0.0, 1.0);
    uv = texCoords;
    cutoff = cutoffIn;
    width = widthIn;
    length = lengthIn;
}
