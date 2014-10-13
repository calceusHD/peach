

#include <string.h>

#include "Tile.h"
#include "GL/glew.h"

Tile::Tile() {
    glGenBuffers(1, &glBuffer);
    glGenVertexArrays(1, &glVao);
    glBindVertexArray(glVao);
    glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
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
    float *buffer = new float[3 * vertCount];
    int offs = 0;
    for (int i = 0; i < strokes.size(); ++i)
    {
        Stroke* s = strokes.at(i);
        memcpy(buffer + offs * 3, s->points, 3 * s->pointCount * sizeof(float));
        firsts[i] = offs;
        counts[i] = s->pointCount;
        offs += s->pointCount;
    }
    glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * vertCount * sizeof(float), buffer, GL_STATIC_DRAW);
    
    delete[] buffer;
}