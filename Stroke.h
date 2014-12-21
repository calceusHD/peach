

#ifndef STROKE_H
#define	STROKE_H

#include <glm/glm.hpp>
#include <cstdio>

class Stroke {
public:
    glm::vec2* m_linePts;
    unsigned int m_lineCnt;
    float m_lineWidth;
    unsigned long m_id;
    Stroke(glm::vec2* lineData, unsigned int cnt, float width);
    Stroke(const Stroke& orig);
    void setWidth(float width);
    unsigned int getId();
    unsigned int generateVertexData(glm::vec2* tgtPoints, glm::vec4* tgtAux);
    virtual ~Stroke();
private:

};

#endif	/* STROKE_H */

