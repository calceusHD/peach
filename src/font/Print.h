

#ifndef PRINT_H_
#define PRINT_H_

#include <cstdarg>
#include <cstring>
#include <cwchar>
#include "Print.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Matrix.h"
#include "gl/Program.h"
#include "Font.h"
#include <glm/gtc/type_ptr.hpp>

class Print {
public:
	Program _program;
    Font *_font;
    unsigned int _vbo[2];
    unsigned int _vao;
    glm::mat4 _mat;
    Vec2<unsigned int> _screen;
    
    unsigned int m_stepSize, m_tex, m_charMat;

	Print(Font *font);
	virtual ~Print();

	void printfAt(float x, float y, float sx, float sy, const char *fmt, ...);
	static unsigned int getUcs4CharFromString(uint32_t *out, unsigned char *in);
	void setScreenSize(Vec2<unsigned int> size);
};

#endif /* PRINT_H_ */
