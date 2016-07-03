

#ifndef TILERENDERER_H
#define	TILERENDERER_H

#include "Tile.h"
#include <GL/glew.h>
#include <cstdio>
#include "gl/Program.h"
#include "font/Vec2.h"
#include "font/Matrix.h"

class TileRenderer {
public:
    glm::vec2 camera_offset;
    glm::i64vec2 camera_offset_i;

    Program program;
    Vec2<unsigned int> size;
    unsigned int sizeUniform;
    unsigned int mvpUniform;
    unsigned int debugUniform;
    unsigned int posUniform;
    glm::mat4 mvp;
    bool debug;
    
    TileRenderer();
    TileRenderer(const TileRenderer& orig);
    virtual ~TileRenderer();
    
    void setDebug(bool on);
    bool getDebug();
    void setScreenSize(Vec2<unsigned int> size);
    void renderTile(Tile* t);
    void offsetCamera(glm::vec2 off);
    void setCamera(glm::i64vec2 off_i, glm::vec2 off);
private:

};

#endif	/* TILERENDERER_H */

