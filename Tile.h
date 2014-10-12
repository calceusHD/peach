

#ifndef TILE_H
#define	TILE_H

#include <glm/glm.hpp>
#include <vector>
#include "Stroke.h"

class Tile {
public:
    glm::vec2 offset;
    std::vector<Stroke*> strokes;
    
    int* firsts = nullptr;
    int* counts = nullptr;
    unsigned int glBuffer, glVao;
    
    Tile();
    Tile(const Tile& orig);
    void addStroke(Stroke* s);
    void generateTileData();
    
    virtual ~Tile();
private:

};

#endif	/* TILE_H */

