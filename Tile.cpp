

#include <string.h>
#include <cmath>

#include "Tile.h"
#include "GL/glew.h"

Tile::Tile() {
    glGenBuffers(1, &glBuffer);
    glGenVertexArrays(1, &glVao);
    glBindVertexArray(glVao);
    glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    //addStroke(new Stroke((glm::vec2*)new float[8]{TILE_SIZE, 0.0f, TILE_SIZE, TILE_SIZE, 0.0f, 0.0f, 0.0f, TILE_SIZE}, 4, 0.04f));
    addStroke(new Stroke((glm::vec2*)new float[8]{0.2f, 0.3f, 0.3f, -0.3f, 0.25f, 0.3f}, 3, 0.04f));
    addStroke(new Stroke((glm::vec2*)new float[8]{0.0f, 0.3f, -0.1f, -0.3f, -0.05f, 0.3f}, 3, 0.04f));
    //addStroke(new Stroke((glm::vec2*)new float[8]{TILE_SIZE, 0.0f, TILE_SIZE, TILE_SIZE, 0.0f, 0.0f, 0.0f, TILE_SIZE}, 4, 0.04f));
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
    float *buffer;
    buffer = new float[4 * vertCount];
    int offs = 0;
    for (int i = 0; i < strokes.size(); ++i)
    {
        Stroke* s = strokes.at(i);
        memcpy(buffer + offs * 4, s->points, 4 * s->pointCount * sizeof(float));
        firsts[i] = offs;
        counts[i] = s->pointCount;
        offs += s->pointCount;
    }
    glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertCount * sizeof(float), buffer, GL_STATIC_DRAW);
    
    //delete[] buffer;
}

void Tile::getTilePosition(glm::ivec2* out, glm::vec2 in) {
    out->x = std::floor(in.x / TILE_SIZE);
    out->y = std::floor(in.y / TILE_SIZE);
}