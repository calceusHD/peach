#include "Drawing.h"
#include "Tile.h"
#include "TileRenderer.h"
#include <cstdint>

Drawing::Drawing(TileRenderer* tr) : m_tiles(&cmpfn) {
    m_tr = tr;
    for (int64_t i = -9; i < 10; ++i) {
        for (int64_t j = -9; j < 10; ++j) {
            m_tiles[glm::i64vec2(i, j)] = new Tile(glm::i64vec2(i, j));
        }
    }
}

bool Drawing::cmpfn(glm::i64vec2 lhs, glm::i64vec2 rhs) {
    if (lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    } else {
        return lhs.y < rhs.y;
    }

}

void Drawing::render() {
    for (auto t: m_tiles) {
        m_tr->renderTile(t.second);
    }
}

Drawing::Drawing(const Drawing& orig) {
}

Drawing::~Drawing() {
}

