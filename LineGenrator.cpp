/* 
 * File:   lineGenrator.cpp
 * Author: tab
 * 
 * Created on 24 October 2014, 13:36
 */

#include "LineGenrator.h"

LineGenrator::LineGenrator() {
}

LineGenrator::LineGenrator(const LineGenrator& orig) {
}

LineGenrator::~LineGenrator() {
}

unsigned int LineGenrator::generateStroke(bool first, bool last, glm::vec2 cur, glm::vec2 next, glm::vec2 prev, glm::vec2* tgtXy, glm::vec4* tgtAux, float width, unsigned int count) {
    glm::vec2 lineP = first ? glm::vec2(0.0f) : cur - prev;
    glm::vec2 lineN = last ? glm::vec2(0.0f) : next - cur;

    glm::vec2 normalP = glm::normalize(glm::vec2(-lineP.y, lineP.x));
    glm::vec2 normalN = glm::normalize(glm::vec2(-lineN.y, lineN.x));
    glm::vec2 normal = first ? normalN : normalP;
    glm::vec2 tangent;
    if (first)
    {
        tangent = lineN;
    }
    else if (last)
    {
        tangent = lineP;

    }
    else
    {
        tangent = glm::normalize(glm::normalize(next - cur) + glm::normalize(cur - prev));
    }
    glm::vec2 miter = glm::vec2(-tangent.y, tangent.x);
    float scale = 1 / glm::dot(miter, normal);
    float length = width * scale;
    float v1 = (count % 2) == 0 ? 1.0f : 0.0f;
    float v2 = (count % 2) == 0 ? 0.0f : 1.0f;
    if (scale > 1.7 && !first && !last)
    {
        float lim = std::min(length, std::max(glm::length(lineP), glm::length(lineN)));
        printf("corner too sharp!%f, id:%i/%i, %f\n", tgtXy, tgtXy, scale, glm::dot(normalP, lineN));
        if (glm::dot(normalP, lineN) < 0)
        {
            tgtXy[0] = cur + normalP * width;
            tgtAux[0] = glm::vec4(1.0f, v1, width, 0.0f);
            tgtXy[1] = cur - miter * lim;
            tgtAux[1] = glm::vec4(0.0f, v1, width, 0.0f);

            tgtXy[2] = cur + normalN * width;
            tgtAux[2] = glm::vec4(1.0f, v2, 0.5f*(width + lim), 0.0f);
            tgtXy[3] = cur - miter * lim;
            tgtAux[3] = glm::vec4(0.0f, v2, 0.5f*(width + lim), 0.0f);
        }
        else
        {
            tgtXy[0] = cur + miter * lim;
            tgtAux[0] = glm::vec4(1.0f, v1, width, 0.0f);
            tgtXy[1] = cur - normalP * width;
            tgtAux[1] = glm::vec4(0.0f, v1, width, 0.0f);

            tgtXy[2] = cur + miter * lim;
            tgtAux[2] = glm::vec4(1.0f, v2, 0.5f*(width + lim), 0.0f);
            tgtXy[3] = cur - normalN * width;
            tgtAux[3] = glm::vec4(0.0f, v2, 0.5f*(width + lim), 0.0f);
            
        }
        return 2;
            
    }
    else
    {
        tgtXy[0] = cur + miter * length;
        tgtAux[0] = glm::vec4(1.0f, v1, width, 0.0f);

        tgtXy[1] = cur - miter * length;
        tgtAux[1] = glm::vec4(0.0f, v1, width, 0.0f);
        return 1;
    }
    
}




