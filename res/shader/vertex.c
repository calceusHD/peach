

#version 300 es

layout(location = 0) in vec4 pos;


void main(void)
{
	gl_Position = vec4(pos.xy, 0.0, 1.0);
}
