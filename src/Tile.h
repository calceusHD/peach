

#ifndef TILE_H
#define	TILE_H

#include <glm/glm.hpp>
#include <vector>
#include "Stroke.h"

class Tile {
public:

    static constexpr const float TILE_SIZE = 512.0f / 1000.0f;
    glm::vec2 m_offset;
    std::vector<Stroke*> m_strokes;
    bool m_dirty;
    
    int* m_firsts = nullptr;
    int* m_counts = nullptr;
    unsigned int m_glBuffer, m_glVao;
    
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

