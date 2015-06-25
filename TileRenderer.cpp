

#include "TileRenderer.h"
#include "Stroke.h"
#include "Tile.h"
#include "gl/Program.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

TileRenderer::TileRenderer() : mvp(1.0f),
    debug(false) {
    
    program.attach(new Shader("res/shader/vertex.c", true, GL_VERTEX_SHADER));
    program.attach(new Shader("res/shader/fragment.c", true, GL_FRAGMENT_SHADER));
    
    program.build();

    debugUniform = program.getUniformLocation("debug");
    sizeUniform = program.getUniformLocation("size");
    mvpUniform = program.getUniformLocation("mvp");
}


TileRenderer::~TileRenderer() {
    
    
}

void TileRenderer::renderTile(Tile* t) {
    t->generateTileData();
    program.use();
    glUniform1f(sizeUniform, size.length());
    glUniform1i(debugUniform, debug);
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));
    glBindVertexArray(t->m_glVao);
    glMultiDrawArrays(debug ? GL_LINE_STRIP : GL_TRIANGLE_STRIP, t->m_firsts, t->m_counts, t->m_strokes.size());
}

void TileRenderer::setScreenSize(glm::uvec2 size) {
    this->size = size;
    
    mvp = glm::scale(glm::mat4(1.0f), glm::vec3(1000.0f/size.x, 1000.0f/size.y, 1.0f));
}

void TileRenderer::setDebug(bool on) {
    debug = on;
}

bool TileRenderer::getDebug() {
    return debug;
}