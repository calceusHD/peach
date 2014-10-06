

#include "Tile.h"

Tile::Tile() {
}

Tile::Tile(const Tile& orig) {
}

Tile::~Tile() {
}

void Tile::addStroke(Stroke* s) {
    strokes.push_back(s);
}
