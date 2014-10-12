

#include "TileRenderer.h"
#include "Stroke.h"
#include "Tile.h"

TileRenderer::TileRenderer() {
}



TileRenderer::TileRenderer(const TileRenderer& orig) {
}

TileRenderer::~TileRenderer() {
}

void TileRenderer::renderTile(Tile* t) {
    glBindVertexArray(t->glVao);
    glMultiDrawArrays(GL_TRIANGLE_STRIP, t->firsts, t->counts, t->strokes.size());
}
