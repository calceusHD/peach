

#ifndef TILERENDERER_H
#define	TILERENDERER_H

#include "Tile.h"
#include <GL/glew.h>
#include <cstdio>

class TileRenderer {
public:
    TileRenderer();
    TileRenderer(const TileRenderer& orig);
    virtual ~TileRenderer();
    void renderTile(Tile* t);
private:

};

#endif	/* TILERENDERER_H */

