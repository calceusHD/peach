
#include "Stroke.h"

Stroke::Stroke(float *lineData, unsigned int cnt, float width) {
    pointCount = cnt * 2;
    points = new float[pointCount * 3];
    for (unsigned int i = 0; i < cnt; ++i)
    {
        glm::vec2 prev = (i == 0) ? glm::vec2(0.0f) : glm::vec2(lineData[(i - 1) * 2], lineData[(i - 1) * 2 + 1]);
        glm::vec2 cur = glm::vec2(lineData[i * 2], lineData[i * 2 + 1]);
        glm::vec2 next = (i + 1 == cnt) ? glm::vec2(0.0f) : glm::vec2(lineData[(i + 1) * 2], lineData[(i + 1) * 2 + 1]);
        
        glm::vec2 line = (i == 0) ? next - cur : cur - prev;
        
        glm::vec2 normal = glm::normalize(glm::vec2(-line.y, line.x));
        glm::vec2 tangent;
        if (i == 0)
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
        float length = width / glm::dot(miter, normal);
        printf("length:%f", length);
        glm::vec2 out = cur + miter * length;
        printf("x:%f, y:%f", out.x, out.y);
        points[i * 6 + 0] = out.x;
        points[i * 6 + 1] = out.y;
        points[i * 6 + 2] = 1.0f;
        out = cur - miter * length;
        points[i * 6 + 3] = out.x;
        points[i * 6 + 4] = out.y;
        points[i * 6 + 5] = 0.0f;
    }
    
    
}

Stroke::Stroke(const Stroke& orig) {
}

Stroke::~Stroke() {
    delete[] points;
}

