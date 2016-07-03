

#include "TileRenderer.h"
#include "Stroke.h"
#include "Tile.h"
#include "gl/Program.h"
#include "font/Matrix.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

TileRenderer::TileRenderer() : mvp(IDENTITY_MATRIX),
    debug(false) {
    
    program.attach(new Shader("res/shader/vertex.c", true, GL_VERTEX_SHADER));
    program.attach(new Shader("res/shader/fragment.c", true, GL_FRAGMENT_SHADER));
    
    program.build();

    debugUniform = program.getUniformLocation("debug");
    sizeUniform = program.getUniformLocation("size");
    mvpUniform = program.getUniformLocation("mvp");
    posUniform = program.getUniformLocation("offset");
}


TileRenderer::~TileRenderer() {
    
    
}

void TileRenderer::offsetCamera(glm::vec2 off) {
    camera_offset += off * glm::vec2(-1.0f, 1.0f);
    printf("i got offset: %f %f\n", off.x, off.y);
    camera_offset.x -= trunc(camera_offset.x/Tile::TILE_SIZE) * Tile::TILE_SIZE;
    camera_offset.y -= trunc(camera_offset.y/Tile::TILE_SIZE) * Tile::TILE_SIZE;
}

void TileRenderer::renderTile(Tile* t) {
    t->generateTileData();
    program.use();
    glUniform2f(posUniform, t->getPosition().x * Tile::TILE_SIZE + camera_offset.x, t->getPosition().y * Tile::TILE_SIZE + camera_offset.y);
    glUniform1f(sizeUniform, size.length());
    glUniform1i(debugUniform, debug);
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));
    glBindVertexArray(t->m_glVao);
    glMultiDrawArrays(debug ? GL_LINE_STRIP : GL_TRIANGLES, t->m_firsts, t->m_counts, t->m_strokes.size());
}

void TileRenderer::setScreenSize(Vec2<unsigned int> size) {
    this->size = size;
    
    mvp = glm::scale(glm::mat4(1.0f), glm::vec3(1000.0f/size.x, 1000.0f/size.y, 1.0f));
}

void TileRenderer::setDebug(bool on) {
    debug = on;
}

bool TileRenderer::getDebug() {
    return debug;
}
