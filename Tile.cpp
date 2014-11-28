

#include <string.h>
#include <cmath>
#include <cstdio>

#include "Tile.h"
#include "GL/glew.h"

Tile::Tile() {
    glGenBuffers(2, m_glBuffer);
    glGenVertexArrays(1, &m_glVao);
    glBindVertexArray(m_glVao);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_glBuffer[0]);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_glBuffer[1]);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
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
    m_strokes.push_back(s);
    generateTileData();
}

void Tile::generateTileData() {
    unsigned int maxVertCount = 0;
    unsigned int vertCount = 0;
    for (Stroke* s : m_strokes)
    {
        maxVertCount += s->m_lineCnt * 2 + s->m_lineCnt;
    }
    delete[] m_firsts;
    delete[] m_counts;
    m_firsts = new int[m_strokes.size()];
    m_counts = new int[m_strokes.size()];
    
    glm::vec2* bufferXy = new glm::vec2[maxVertCount];
    glm::vec4* bufferAux = new glm::vec4[maxVertCount];
    
    int offs = 0;
    for (int i = 0; i < m_strokes.size(); ++i)
    {
        Stroke* s = m_strokes.at(i);
        unsigned int verts = s->generateVertexData(bufferXy + offs * 2, bufferAux + offs * 2);
        offs += verts;
        m_firsts[i] = offs * 2;
        m_counts[i] = verts * 2;
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_glBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, offs * 2 * sizeof(glm::vec2), bufferXy, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_glBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, offs * 2 * sizeof(glm::vec4), bufferAux, GL_STATIC_DRAW);
    
    delete[] bufferXy;
    delete[] bufferAux;
}

void Tile::getTilePosition(glm::ivec2* out, glm::vec2 in) {
    out->x = std::floor(in.x / TILE_SIZE);
    out->y = std::floor(in.y / TILE_SIZE);
}