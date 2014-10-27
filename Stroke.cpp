
#include "Stroke.h"
#include "LineGenrator.h"


Stroke::Stroke(glm::vec2* lineData, unsigned int cnt, float width) {
    pointCount = cnt * 2;
    points = new glm::vec4[pointCount + cnt]; // => pointCount * 1.5
    unsigned int i = 0;
    unsigned int pointCnt = 0;
    while (i < cnt)
    {
        bool first = (i == 0);
        bool last = (i + 1 == cnt);
        glm::vec2 prev = first ? glm::vec2(0.0f) : lineData[i - 1];
        glm::vec2 cur = lineData[i];
        glm::vec2 next = last ? glm::vec2(0.0f) : lineData[i + 1];
        
        pointCnt += LineGenrator::generateStroke(first, last, cur, next, prev, points + sizeof(glm::vec4) * pointCnt, width);
        /*
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
        else if (i + 1 == cnt)
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
            printf("corner too sharp!%f, id:%i/%i, %f\n", scale, i, cnt, width);
            glm::vec2 out = cur + normalP * width;
            points[pointCnt * 2 + 0] = glm::vec4(out, 1.0f, width);
            out = cur - miter * width * 2.0f;
            points[pointCnt * 2 + 1] = glm::vec4(out, 0.0f, width);
            ++pointCnt;
            
            out = cur + normalN * width;
            points[pointCnt * 2 + 0] = glm::vec4(out, 1.0f, width);
            out = cur - miter * width * 2.0f;
            points[pointCnt * 2 + 1] = glm::vec4(out, 0.0f, width);
            ++pointCnt;
        }
        else
        {
            glm::vec2 out = cur + miter * length;
            points[pointCnt * 2 + 0] = glm::vec4(out, 1.0f, width);
            
            out = cur - miter * length;
            points[pointCnt * 2 + 1] = glm::vec4(out, 0.0f, width);
            ++pointCnt;
        }
        */
        
        ++i;
    }
    pointCount = pointCnt * 2;
    
}

Stroke::Stroke(const Stroke& orig) {
}

Stroke::~Stroke() {
    delete[] points;
}

