

#ifndef STROKE_H
#define	STROKE_H

#include <glm/glm.hpp>
#include <cstdio>

class Stroke {
public:
    glm::vec2* points;
    glm::vec4* pointsAux;
    unsigned int pointCount;
    unsigned long id;
    Stroke(glm::vec2* lineData, unsigned int cnt, float width);
    Stroke(const Stroke& orig);
    virtual ~Stroke();
private:

};

#endif	/* STROKE_H */

