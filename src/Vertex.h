/* 
 * File:   Vertex.h
 * Author: Henry
 *
 * Created on 04 January 2015, 18:06
 */

#ifndef VERTEX_H
#define	VERTEX_H


#include <glm/glm.hpp>


class Vertex {
public:
    glm::vec2 pos;
    glm::vec2 m_texCoords;
    float length;
    glm::vec2 m_cutoff;
    float width;
    glm::vec2 rotation;
    
    Vertex() : pos(0.0f), m_texCoords(0.0f), length(0.0f), m_cutoff(0.0f), width(0.0f), rotation(0.0f) {};
    Vertex(glm::vec2 pos, glm::vec2 texCoords, float width, const glm::vec2 cutoff, float length, glm::vec2 rotation) : 
        pos(pos), m_texCoords(texCoords), length(length), m_cutoff(cutoff), width(width), rotation(rotation) {};

};

#endif	/* VERTEX_H */

