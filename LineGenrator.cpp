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

unsigned int LineGenrator::generateStroke(bool first, bool last, glm::vec2 cur, glm::vec2 next, glm::vec2 prev, glm::vec4* tgt, float width) {
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
    if (scale > 1.7 && !first && !last)
    {
        printf("corner too sharp!%f, id:%i/%i, %f\n", scale, width);
        glm::vec2 out = cur + normalP * width;
        tgt[0] = glm::vec4(out, 1.0f, width);
        out = cur - miter * width * 2.0f;
        tgt[1] = glm::vec4(out, 0.0f, width);

        out = cur + normalN * width;
        tgt[2] = glm::vec4(out, 1.0f, width);
        out = cur - miter * width * 2.0f;
        tgt[3] = glm::vec4(out, 0.0f, width);
        return 2;
    }
    else
    {
        glm::vec2 out = cur + miter * length;
        tgt[0] = glm::vec4(out, 1.0f, width);

        out = cur - miter * length;
        tgt[1] = glm::vec4(out, 0.0f, width);
        return 1;
    }
    
}




