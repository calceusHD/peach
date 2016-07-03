#include <map>
#include <glm/glm.hpp>
#ifndef DRAWING_H
#define DRAWING_H

class TileRenderer;
class Tile;

class Drawing {
public:
    Drawing(TileRenderer* tr);
    Drawing(const Drawing& orig);
    virtual ~Drawing();
    void render();
    TileRenderer* m_tr;    

private:
    static bool cmpfn(glm::i64vec2 lhs, glm::i64vec2 rhs);

    std::map<glm::i64vec2, Tile*, bool(*)(glm::i64vec2, glm::i64vec2)> m_tiles;

};

#endif /* DRAWING_H */

