/* 
 * File:   lineGenrator.h
 * Author: tab
 *
 * Created on 24 October 2014, 13:36
 */

#ifndef LINEGENRATOR_H
#define	LINEGENRATOR_H

#include <glm/glm.hpp>
#include <cstdio>

class LineGenrator {
public:
    LineGenrator();
    LineGenrator(const LineGenrator& orig);
    virtual ~LineGenrator();
    
    static unsigned int generateStroke(bool first, bool last, glm::vec2 cur, glm::vec2 next, glm::vec2 prev, glm::vec4 *tgt, float width);
private:

};

#endif	/* LINEGENRATOR_H */

