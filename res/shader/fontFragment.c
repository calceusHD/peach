/*
 * fragment.c
 *
 *  Created on: Mar 16, 2013
 *      Author: ICH
 */

#version 330 core

uniform sampler2DArray tex;

uniform sampler2D tex2;

flat in uint charDataOut;
layout(location = 0) out vec4 fragColor;
in vec2 texCoords;
uniform float stepSize;

uniform float color;

void main(void)
{
    
    //float tmp = charDataOut / 256.0;
    //float tmp = texture(tex, texCoords).r;
    float nStepSize = max(0, min(0.5, stepSize));
	
	uint iTmp = charDataOut / 4U;
	
	vec4 tmp = texture(tex, vec3(texCoords, max(0, min(0x100 - 1, floor(float(iTmp) + 0.5)))));
	
	float fTmp = 0;
	switch ( charDataOut % 4U )
	{
		case 0U:
			fTmp = tmp.r;
			break;
		case 1U:
			fTmp = tmp.g;
			break;
		case 2U:
			fTmp = tmp.b;
			break;
		case 3U:
			fTmp = tmp.a;
			break;
		
	
	}
	
    //float tmp2 = texture(tex2, texCoords).r;

    fTmp = smoothstep(0.5 - nStepSize, 0.5 + nStepSize, fTmp);


    fragColor = vec4(1.0, 1.0, 1.0, fTmp);
}
