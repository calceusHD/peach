#version 300 es

layout(location = 0) out highp vec4 fragColor;
in highp vec2 uv;
flat in highp float width;
flat in highp float length;
flat in highp vec2 cutoff;
uniform highp int debug;
uniform highp float size;
void main(void)
{
    highp float diff = 2.8 / width / 1000.0;
    highp vec2 diffY = 2.8 / cutoff / 1000.0;
    highp float min, max;
    highp float minY, maxY;
    if (uv.y > 0.5)
    {
        maxY = 1.0;
        minY = 1.0 - diffY.x;
    }
    else
    {
        maxY = 0.0;
        minY = diffY.y;
    }
    if (uv.x > 0.5)
    {
        max = 1.0;
        min = 1.0 - diff;
    }
    else
    {
        max = 0.0;
        min = diff;
    }
    if (debug != 0)
        fragColor = vec4(1.0, 1.0, 0.0, 1.0);
    else
        fragColor = vec4(1.0, smoothstep(maxY, minY, uv.y), 0.0, smoothstep(max, min, uv.x));
}
