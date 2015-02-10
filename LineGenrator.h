
#ifndef LINEGENRATOR_H
#define	LINEGENRATOR_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>

#include <cstdio>
#include <cmath>
#include "Vertex.h"

class LineGenrator {
public:
    LineGenrator();
    LineGenrator(const LineGenrator& orig);
    virtual ~LineGenrator();
    
    static unsigned int generateStroke(bool first, bool last, glm::vec2 cur, glm::vec2 next, glm::vec2 prev, Vertex* tgt, float width, unsigned int count);
private:

};

#endif	/* LINEGENRATOR_H */

