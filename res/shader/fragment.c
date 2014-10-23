

#version 300 es

layout(location = 0) out highp vec4 fragColor;
in highp float uv;
in highp float width;
uniform highp float size;
void main(void)
{
    highp float diff = 2.8 / width / size;
    highp float min, max;
    if (uv > 0.5)
    {
        max = 1.0;
        min = 1.0 - diff;
    }
    else
    {
        max = 0.0;
        min = diff;
    }
    fragColor = vec4(1.0, 1.0, 0.0, smoothstep(max, min, uv));
}
