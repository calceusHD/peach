
#ifndef LINEGENRATOR_H
#define	LINEGENRATOR_H

#include <glm/glm.hpp>
#include <cstdio>
#include <cmath>

class LineGenrator {
public:
    LineGenrator();
    LineGenrator(const LineGenrator& orig);
    virtual ~LineGenrator();
    
    static unsigned int generateStroke(bool first, bool last, glm::vec2 cur, glm::vec2 next, glm::vec2 prev, glm::vec2* tgtXy, glm::vec4* tgtAux, float width, unsigned int count);
private:

};

#endif	/* LINEGENRATOR_H */

