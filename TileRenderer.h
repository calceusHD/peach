

#ifndef TILERENDERER_H
#define	TILERENDERER_H

#include "Tile.h"
#include <GL/glew.h>
#include <cstdio>
#include "gl/Program.h"
#include "glm/glm.hpp"
#include "font/Vec2.h"

class TileRenderer {
public:
    Program program;
    glm::uvec2 size;
    unsigned int sizeUniform;
    unsigned int mvpUniform;
    unsigned int debugUniform;
    bool debug;
    glm::mat4 mvp;
    TileRenderer();
    TileRenderer(const TileRenderer& orig);
    virtual ~TileRenderer();
    
    void setDebug(bool on);
    bool getDebug();
    void setScreenSize(glm::uvec2 size);
    void renderTile(Tile* t);
private:

};

#endif	/* TILERENDERER_H */

