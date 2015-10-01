

#include <string.h>
#include <cmath>
#include <cstdio>

#include "Tile.h"
#include "GL/glew.h"

Tile::Tile() {
    glGenBuffers(1, &m_glBuffer);
    glGenVertexArrays(1, &m_glVao);
    glBindVertexArray(m_glVao);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_glBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, width));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, cutoff));
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, length));
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, rotation));
    
    
    
    //addStroke(new Stroke((glm::vec2*)new float[8]{TILE_SIZE, 0.0f, TILE_SIZE, TILE_SIZE, 0.0f, 0.0f, 0.0f, TILE_SIZE}, 4, 0.04f));
    addStroke(new Stroke((glm::vec2*)new float[8]{0.43f, 0.3f, 0.3f, -0.3f, 0.25f, 0.3f}, 3, 0.04f));
    addStroke(new Stroke((glm::vec2*)new float[8]{0.2f, -0.3f, -0.1f, -0.3f, -0.05f, 0.3f}, 3, 0.04f));
    //addStroke(new Stroke((glm::vec2*)new float[8]{TILE_SIZE, 0.0f, TILE_SIZE, TILE_SIZE, 0.0f, 0.0f, 0.0f, TILE_SIZE}, 4, 0.04f));
}

Tile::Tile(const Tile& orig) {
}

Tile::~Tile() {
}

void Tile::addStroke(Stroke* s) {
    m_strokes.push_back(s);
    m_dirty = true;
}

void Tile::generateTileData() {
    if (!m_dirty)
        return;
    m_dirty = false;
    unsigned int maxVertCount = 0;
    for (Stroke* s : m_strokes)
    {
        maxVertCount += s->m_lineCnt * 6;
    }
    delete[] m_firsts;
    delete[] m_counts;
    m_firsts = new int[m_strokes.size()];
    m_counts = new int[m_strokes.size()];
    
    Vertex* buffer = new Vertex[maxVertCount];
    
    int offs = 0;
    for (int i = 0; i < m_strokes.size(); ++i)
    {
        Stroke* s = m_strokes.at(i);
        unsigned int verts = s->generateVertexData(buffer + offs);
        m_firsts[i] = offs;
        m_counts[i] = verts;
        
        offs += verts;
    }
    printf("vertices: %i of %i", offs, maxVertCount);
    glBindBuffer(GL_ARRAY_BUFFER, m_glBuffer);
    glBufferData(GL_ARRAY_BUFFER, offs * sizeof(Vertex), buffer, GL_STATIC_DRAW);
    
    delete[] buffer;
}

void Tile::getTilePosition(glm::ivec2* out, glm::vec2 in) {
    out->x = std::floor(in.x / TILE_SIZE);
    out->y = std::floor(in.y / TILE_SIZE);
}