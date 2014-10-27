

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
    Program program;
    Vec2<unsigned int> size;
    unsigned int sizeUniform;
    unsigned int mvpUniform;
    unsigned int debugUniform;
    bool debug;
    Matrix<float> mvp;
    TileRenderer();
    TileRenderer(const TileRenderer& orig);
    virtual ~TileRenderer();
    
    void setDebug(bool on);
    bool getDebug();
    void setScreenSize(Vec2<unsigned int> size);
    void renderTile(Tile* t);
private:

};

#endif	/* TILERENDERER_H */

