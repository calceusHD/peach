

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

unsigned int Stroke::generateVertexData(Vertex* tgt) {
    unsigned int i = 0;
    unsigned int pointCnt = 0;
    while (i < m_lineCnt)
    {
        bool first = (i == 0);
        bool last = (i == m_lineCnt - 1);
        glm::vec2 prev = first ? glm::vec2(0.0f) : m_linePts[i - 1];
        glm::vec2 cur = m_linePts[i];
        glm::vec2 next = last ? glm::vec2(0.0f) : m_linePts[i + 1];
        pointCnt += LineGenrator::generateStroke(first, last, cur, next, prev, tgt + pointCnt, m_lineWidth, pointCnt);
        ++i;
    }
    return pointCnt;
}

void Stroke::setWidth(float width) {
    m_lineWidth = width;
}

unsigned int Stroke::getId() {
    return m_id;
}


