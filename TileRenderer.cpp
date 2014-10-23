

#include "TileRenderer.h"
#include "Stroke.h"
#include "Tile.h"
#include "gl/Program.h"
#include "font/Matrix.h"

TileRenderer::TileRenderer() : mvp(IDENTITY_MATRIX) {
    
    program.attach(new Shader("res/shader/vertex.c", true, GL_VERTEX_SHADER));
    program.attach(new Shader("res/shader/fragment.c", true, GL_FRAGMENT_SHADER));
    
    program.build();

    sizeUniform = program.getUniformLocation("size");
    mvpUniform = program.getUniformLocation("mvp");
}


TileRenderer::~TileRenderer() {
    
    
}

void TileRenderer::renderTile(Tile* t) {
    program.use();
    glUniform1f(sizeUniform, size.length());
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, mvp.data.data());
    glBindVertexArray(t->glVao);
    glMultiDrawArrays(GL_TRIANGLE_STRIP, t->firsts, t->counts, t->strokes.size());
}

void TileRenderer::setScreenSize(Vec2<unsigned int> size) {
    this->size = size;
    
    mvp.set(IDENTITY_MATRIX);
    mvp.scale(1000.0f/size.x, 1000.0f/size.y, 1.0f);
}
