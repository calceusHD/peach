

#include <string.h>
#include <X11/Xdefs.h>

#include "Tile.h"
#include "GL/glew.h"

Tile::Tile() {
    glGenBuffers(1, &glBuffer);
}

Tile::Tile(const Tile& orig) {
}

Tile::~Tile() {
}

void Tile::addStroke(Stroke* s) {
    strokes.push_back(s);
    generateTileData();
}

void Tile::generateTileData() {
    unsigned int vertCount = 0;
    for (Stroke* s : strokes)
    {
        vertCount += s->pointCount;
    }
    delete[] firsts;
    delete[] counts;
    firsts = new int[strokes.size()];
    counts = new int[strokes.size()];
    float *buffer = new float[2 * vertCount];
    int offs = 0;
    for (int i = 0; i < strokes.size(); ++i)
    {
        Stroke* s = strokes.at(i);
        memcpy(buffer + offs * 2, s->points, 2 * s->pointCount * sizeof(float));
        firsts[i] = offs;
        counts[i] = s->pointCount;
        offs += s->pointCount;
    }
    glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * vertCount * sizeof(float), buffer, GL_STATIC_DRAW);
    
    delete[] buffer;
}