

#ifndef PRINT_H_
#define PRINT_H_

#include <cstdarg>
#include <cstring>
#include <cwchar>
#include "Print.h"
#include "gl/Program.h"
#include "Font.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class Print {
public:
	Program m_Program;
    Font *m_Font;
    unsigned int m_Vbo[2];
    unsigned int m_Vao;
    glm::mat4 _mat;
    glm::uvec2 _screen;
    
    unsigned int m_stepSize, m_tex, m_charMat;

	Print(Font *font);
	virtual ~Print();

	void printfAt(float x, float y, float sx, float sy, const char *fmt, ...);
	static unsigned char* getUcs4CharFromString(uint32_t* out, unsigned char* in);
	void setScreenSize(glm::uvec2 size);
};

#endif /* PRINT_H_ */
