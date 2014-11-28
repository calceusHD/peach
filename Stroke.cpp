

#include "Stroke.h"
#include "LineGenrator.h"
#include <memory.h>


Stroke::Stroke(glm::vec2* lineData, unsigned int cnt, float width) {
    m_linePts = new glm::vec2[cnt];
    m_lineCnt = cnt;
    m_lineWidth = width;
    memcpy(m_linePts, lineData, cnt * sizeof(glm::vec2));
    
    

}

Stroke::Stroke(const Stroke& orig) {
}

Stroke::~Stroke() {
    delete[] m_linePts;
}

unsigned int Stroke::generateVertexData(glm::vec2* tgtPoints, glm::vec4* tgtAux) {
    unsigned int i = 0;
    unsigned int pointCnt = 0;
    while (i < m_lineCnt)
    {
        bool first = (i == 0);
        bool last = (i + 1 == m_lineCnt);
        glm::vec2 prev = first ? glm::vec2(0.0f) : m_linePts[i - 1];
        glm::vec2 cur = m_linePts[i];
        glm::vec2 next = last ? glm::vec2(0.0f) : m_linePts[i + 1];
        pointCnt += LineGenrator::generateStroke(first, last, cur, next, prev, tgtPoints + 2 * pointCnt, tgtAux + 2 * pointCnt, m_lineWidth, pointCnt);
        ++i;
    }
    return pointCnt;
}

