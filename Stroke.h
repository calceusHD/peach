

#ifndef STROKE_H
#define	STROKE_H

#include <glm/glm.hpp>
#include <cstdio>

class Stroke {
public:
    float *points;
    unsigned int pointCount;
    Stroke(float *lineData, unsigned int cnt, float width);
    Stroke(const Stroke& orig);
    virtual ~Stroke();
private:

};

#endif	/* STROKE_H */

