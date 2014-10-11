

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
    glBindBuffer(GL_ARRAY_BUFFER, t->glBuffer);
    printf("cnt:%i", t->strokes.size());
    glMultiDrawArrays(GL_TRIANGLE_STRIP, t->firsts, t->counts, t->strokes.size());
}
