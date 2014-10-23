

#version 300 es

layout(location = 0) in vec4 pos;
out highp float uv;
out highp float width;
uniform highp mat4 mvp;
void main(void)
{
    gl_Position = mvp * vec4(pos.xy, 0.0, 1.0);
    uv = pos.z;
    width = pos.w;
}
