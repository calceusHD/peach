/* 
 * File:   Util.cpp
 * Author: deb
 * 
 * Created on 03 November 2015, 12:50
 */

#include "Util.h"

Util::Util() {
}

glm::vec2 Util::screen2gl(glm::vec2 in, Vec2<unsigned int> screen) {
    return glm::vec2((in.x / screen.x - 0.5f) * 2.0f * screen.x / 1000.0f,
                            -(in.y / screen.y - 0.5f) * 2.0f * screen.y / 1000.0f);
}

Util::Util(const Util& orig) {
}

Util::~Util() {
}

