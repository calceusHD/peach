

#ifndef TILE_H
#define	TILE_H

#include <glm/glm.hpp>
#include <vector>
#include "Stroke.h"

class Tile {
public:
    static constexpr const float TILE_SIZE = 512.0f / 1000.0f;
    glm::vec2 offset;
    std::vector<Stroke*> strokes;
    
    int* firsts = nullptr;
    int* counts = nullptr;
    unsigned int glBuffer, glVao;
    
    Tile();
    Tile(const Tile& orig);
    void addStroke(Stroke* s);
    void generateTileData();
    bool isInTile(glm::vec2 pnt);
    static void getTilePosition(glm::ivec2* out, glm::vec2 in);
    
    virtual ~Tile();
private:

};

#endif	/* TILE_H */

