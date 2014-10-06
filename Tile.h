

#ifndef TILE_H
#define	TILE_H

#include <glm/glm.hpp>
#include <vector>
#include "Stroke.h"

class Tile {
public:
    glm::vec2 offset;
    std::vector<Stroke*> strokes;
    
    Tile();
    Tile(const Tile& orig);
    void addStroke(Stroke* s);
    
    virtual ~Tile();
private:

};

#endif	/* TILE_H */

