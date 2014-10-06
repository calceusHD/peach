

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
    for (Stroke* s : t->strokes)
    {
        //printf("cnt:%i", s->pointCount);
        glBufferData(GL_ARRAY_BUFFER, 2 * s->pointCount * sizeof(float), s->points, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, s->pointCount);
    }
}
