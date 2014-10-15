

#version 300 es

layout(location = 0) out highp vec4 fragColor;
in highp float uv;
void main(void)
{

    fragColor = vec4(1.0, 1.0, 0.0, uv > 0.5 ? smoothstep(1.0, 0.9, uv) : smoothstep(0.0, 0.1, uv));
}
