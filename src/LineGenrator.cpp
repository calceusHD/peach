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
    glm::vec2 line = last ? glm::vec2(0.0f) : next - cur;
    glm::vec2 linePrev = first ? glm::vec2(0.0f) : cur - prev;
    glm::vec2 tangent = glm::normalize(line);
    glm::vec2 tangentPrev = glm::normalize(linePrev);
    glm::vec2 normal = glm::normalize(glm::vec2(-line.y, line.x));
    if (!first && !last) {
        float s = tangent.y * tangentPrev.x - tangent.x * tangentPrev.y;
        float c = tangent.y * tangentPrev.y + tangent.x * tangentPrev.x;
        glm::vec2 rotation = glm::vec2(s, c);
        tgt[0].rotation = rotation;
        tgt[1].rotation = rotation;
        tgt[2].rotation = rotation;
        tgt[3].rotation = rotation;
        tgt[4].rotation = rotation;
        tgt[5].rotation = rotation;
    } else if (!last) {
        glm::vec2 rotation = glm::vec2();
        tgt[0].rotation = rotation;
        tgt[1].rotation = rotation;
        tgt[2].rotation = rotation;
        tgt[3].rotation = rotation;
        tgt[4].rotation = rotation;
        tgt[5].rotation = rotation;
    }
    
    if (!last) {
        float length = glm::length(line);
        float uv = ( length + 2 * width ) / length;
        tgt[0].pos = cur + normal * width - tangent * width;
        tgt[0].m_texCoords = glm::vec2(1.0f, -uv);
        tgt[0].width = width;
        tgt[0].length = length;

        tgt[1].pos = cur - normal * width - tangent * width;
        tgt[1].m_texCoords = glm::vec2(-1.0f, -uv);
        tgt[1].width = width;
        tgt[1].length = length;

        
        tgt[2].pos = next + normal * width + tangent * width;
        tgt[2].m_texCoords = glm::vec2(1.0f, uv);
        tgt[2].width = width;
        tgt[2].length = length;
        
        tgt[3].pos = cur - normal * width  - tangent * width;
        tgt[3].m_texCoords = glm::vec2(-1.0f, -uv);
        tgt[3].width = width;
        tgt[3].length = length;
        
        tgt[4].pos = next - normal * width + tangent * width;
        tgt[4].m_texCoords = glm::vec2(-1.0f, uv);
        tgt[4].width = width;
        tgt[4].length = length;
        
        tgt[5].pos = next + normal * width + tangent * width;
        tgt[5].m_texCoords = glm::vec2(1.0f, uv);
        tgt[5].width = width;
        tgt[5].length = length;
        return 6;
    }   
    return 0;
    
}




