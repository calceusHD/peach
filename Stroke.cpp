
#include "Stroke.h"

Stroke::Stroke(float *lineData, unsigned int cnt, float width) {
    pointCount = cnt * 2;
    points = new float[pointCount * 4];
    for (unsigned int i = 0; i < cnt; ++i)
    {
        bool first = (i == 0);
        bool last = (i + 1 == cnt);
        glm::vec2 prev = first ? glm::vec2(0.0f) : glm::vec2(lineData[(i - 1) * 2], lineData[(i - 1) * 2 + 1]);
        glm::vec2 cur = glm::vec2(lineData[i * 2], lineData[i * 2 + 1]);
        glm::vec2 next = last ? glm::vec2(0.0f) : glm::vec2(lineData[(i + 1) * 2], lineData[(i + 1) * 2 + 1]);
        
        glm::vec2 line = first ? next - cur : cur - prev;
        
        glm::vec2 normal = glm::normalize(glm::vec2(-line.y, line.x));
        glm::vec2 tangent;
        if (first)
        {
            tangent = line;
        }
        else if (i + 1 == cnt)
        {
            tangent = line;
            
        }
        else
        {
            tangent = glm::normalize(glm::normalize(next - cur) + glm::normalize(cur - prev));
        }
        glm::vec2 miter = glm::vec2(-tangent.y, tangent.x);
        float scale = 1 / glm::dot(miter, normal);
        if (scale > 2.0 && !first && !last)
        {
            printf("corner too sharp!%f, id:%i/%i\n", scale, i, cnt);
        }
        float length = width * scale;
        glm::vec2 out = cur + miter * length;
        points[i * 8 + 0] = out.x;
        points[i * 8 + 1] = out.y;
        points[i * 8 + 2] = 1.0f;
        points[i * 8 + 3] = width;
        out = cur - miter * length;
        points[i * 8 + 4] = out.x;
        points[i * 8 + 5] = out.y;
        points[i * 8 + 6] = 0.0f;
        points[i * 8 + 7] = width;
    }
    
    
}

Stroke::Stroke(const Stroke& orig) {
}

Stroke::~Stroke() {
    delete[] points;
}

