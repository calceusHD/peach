/* 
 * File:   Util.h
 * Author: deb
 *
 * Created on 03 November 2015, 12:50
 */

#ifndef UTIL_H
#define	UTIL_H
#include <glm/glm.hpp>
#include "font/Vec2.h"
class Main;

class Util {
public:
    
    static glm::vec2 screen2gl(glm::vec2 in, Vec2<unsigned int> main);
    
    Util();
    Util(const Util& orig);
    virtual ~Util();
private:

};

#endif	/* UTIL_H */

