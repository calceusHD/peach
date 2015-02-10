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

unsigned int LineGenrator::generateStroke(bool first, bool last, glm::vec2 cur, glm::vec2 next, glm::vec2 prev, Vertex* tgt, float width, unsigned int count) {
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
    float v2 = 1.0f - v1;
    if (scale > 1.7 && !first && !last)
    {
        float lim = std::min(length, std::max(glm::length(lineP), glm::length(lineN)));
        printf("corner too sharp!%f, id:%i, %f\n", scale, tgt, glm::dot(normalP, lineN));
        if (glm::dot(normalP, lineN) < 0)
        {
            tgt[0].pos = cur + normalP * width;
            tgt[0].texCoords = glm::vec2(1.0f, v1);
            tgt[0].width = width;
            
            tgt[1].pos = cur - miter * lim;
            tgt[1].texCoords = glm::vec2(0.0f, v1);
            tgt[1].width = width;

            tgt[2].pos = cur + normalN * width;
            tgt[2].texCoords = glm::vec2(1.0f, v2);
            tgt[2].width = 0.5f*(width + lim);
            
            tgt[3].pos = cur - miter * lim;
            tgt[3].texCoords = glm::vec2(0.0f, v2);
            tgt[3].width = 0.5f*(width + lim);
        }
        else
        {
            tgt[0].pos = cur + miter * lim;
            tgt[0].texCoords = glm::vec2(1.0f, v1);
            tgt[0].width = width;
            
            tgt[1].pos = cur - normalP * width;
            tgt[1].texCoords = glm::vec2(0.0f, v1);
            tgt[1].width = width;

            tgt[2].pos = cur + miter * lim;
            tgt[2].texCoords = glm::vec2(1.0f, v2);
            tgt[2].width = 0.5f*(width + lim);
            
            tgt[3].pos = cur - normalN * width;
            tgt[3].texCoords = glm::vec2(0.0f, v2);
            tgt[3].width = 0.5f*(width + lim);
            
        }
        return 2;
            
    }
    else
    {
        glm::vec2 co = glm::vec2(0.0f, width * sqrtf(scale * scale - 1));
        if (count % 2 == 0)
            co = co.xy();
        else
            co = co.yx();
        printf("%f\n", width * sqrtf(scale * scale - 1));

        
        tgt[0].pos = cur + miter * length;
        tgt[0].texCoords = glm::vec2(1.0f, v1);
        tgt[0].width = width;
        tgt[0].cutoff = co;
        tgt[0].length = glm::length(lineN);

        tgt[1].pos = cur - miter * length;
        tgt[1].texCoords = glm::vec2(0.0f, v1);
        tgt[1].width = width;
        tgt[1].cutoff = co;
        tgt[1].length = glm::length(lineN);
        return 1;
    }
    
}




