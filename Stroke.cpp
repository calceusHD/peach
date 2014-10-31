
#include "Stroke.h"
#include "LineGenrator.h"


Stroke::Stroke(glm::vec2* lineData, unsigned int cnt, float width) {
    pointCount = cnt * 2;
    points = new glm::vec4[pointCount + cnt]; // => pointCount * 1.5 is the max count of vertices the edge rounding can create!
    unsigned int i = 0;
    unsigned int pointCnt = 0;
    while (i < cnt)
    {
        bool first = (i == 0);
        bool last = (i + 1 == cnt);
        glm::vec2 prev = first ? glm::vec2(0.0f) : lineData[i - 1];
        glm::vec2 cur = lineData[i];
        glm::vec2 next = last ? glm::vec2(0.0f) : lineData[i + 1];
        pointCnt += LineGenrator::generateStroke(first, last, cur, next, prev, points + 2 * pointCnt, width);
        ++i;
    }
    pointCount = pointCnt * 2;
    
}

Stroke::Stroke(const Stroke& orig) {
}

Stroke::~Stroke() {
    delete[] points;
}

