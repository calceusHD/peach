#version 330

layout(location = 0) out highp vec4 fragColor;
in highp vec2 uv;
flat in highp float width;
flat in highp float length;
flat in highp vec2 cutoff;
flat in highp vec2 rotation;
uniform highp int debug;
uniform highp float size;
void main(void)
{
    highp vec2 uv2;
    highp float diff = 1.0 - 2.0 * 2.8 / width / 1000.0;
    uv2.x = uv.x;
    if (abs(uv.y) < 1.0) {
        uv2.y = 0.0;
    } else {
        uv2.y = ( abs(uv.y) - 1.0 )  * length / ( 2.0 * width);
    }
    highp vec2 uv3 = mat2(rotation.y, rotation.x, -rotation.x, rotation.y) * ((uv + vec2(0.0, 1.0)) * vec2(-1.0, length / ( 2.0 * width)));
    if (uv3.y < 0.0) {
        uv3.y = 0.0;
    }
    //start circle is at (-1.0, 0.0)  ? 

    highp float color = smoothstep(1.0 , diff, uv2.x * uv2.x + uv2.y * uv2.y); // < 0.9 ? 1.0 : 0.0;
    highp float color2;
    if (abs(rotation.x) < 0.1 && abs(rotation.y) < 0.1) {
        color2 = 0.0;
    } else {
        color2 = smoothstep(1.0 , diff, uv3.x * uv3.x + uv3.y * uv3.y);// < 0.9 ? 1.0 : 0.0;
    }
    color *= 1.0;
    color2 *= 1.0;
    fragColor = vec4(vec3(1.0), (color - color2) / (1.0 - color2));
}
