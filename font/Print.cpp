

#include "Print.h"

Print::Print(Font *font) :
_mat(1.0f),
m_Font(font) {

    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);

    glGenBuffers(2, m_Vbo);

    m_Program.attach(new Shader("res/shader/fontVertex.c", true, GL_VERTEX_SHADER));
    m_Program.attach(new Shader("res/shader/fontFragment.c", true, GL_FRAGMENT_SHADER));

    m_Program.build();

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);



    glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, 0, 0);

    glEnableVertexAttribArray(1);

    m_stepSize = m_Program.getUniformLocation("stepSize");
    m_tex = m_Program.getUniformLocation("tex");
    m_charMat = m_Program.getUniformLocation("charMat");

}

Print::~Print() {
    // TODO Auto-generated destructor stub
}

void Print::printfAt(float x, float y, float sx, float sy, const char *fmt, ...) {
    unsigned char *text = new unsigned char[256];

    va_list ap;
    if (fmt == NULL)
        return;
    va_start(ap, fmt);
    vsprintf((char*) text, fmt, ap);
    va_end(ap);

    unsigned int k = strlen((char*) text);

    uint32_t *data = new uint32_t[k * 6];

    struct point {
        float x;
        float y;
        float s;
        float t;
    };


    point *points = new point[k * 6];

    Vec2<float> adv(0.0f, 0.0f);

    unsigned int cCnt = 0;
    unsigned char* textO = text;
    uint32_t ch;
    while (text = getUcs4CharFromString(&ch, text), ch != 0) {
        if (ch == '\n') {
            adv = adv * Vec2<float>(0, 1) + Vec2<float>(0, -1);
        } else {
            unsigned int key = m_Font->getIdFromChar(ch);

            data[cCnt * 6] =
                    data[cCnt * 6 + 1] =
                    data[cCnt * 6 + 2] =
                    data[cCnt * 6 + 3] =
                    data[cCnt * 6 + 4] =
                    data[cCnt * 6 + 5] = key;

            Vec2<float>off = m_Font->m_Glyphs[key].offset / (float) m_Font->m_Size * Vec2<float>(1, 1) + adv;


            points[cCnt * 6 + 0] = (point){off.x, off.y, 0.0f, 1.0f};
            points[cCnt * 6 + 1] = (point){off.x, off.y + 1, 0.0f, 0.0f};
            points[cCnt * 6 + 2] = (point){off.x + 1, off.y + 1, 1.0f, 0.0f};

            points[cCnt * 6 + 3] = (point){off.x, off.y, 0.0f, 1.0f};
            points[cCnt * 6 + 4] = (point){off.x + 1, off.y + 1, 1.0f, 0.0f};
            points[cCnt * 6 + 5] = (point){off.x + 1, off.y, 1.0f, 1.0f};
            Vec2<float> test = m_Font->m_Glyphs[key].advance;
            adv += m_Font->m_Glyphs[key].advance / m_Font->m_Size;
            cCnt++;
        }
    }
    

    m_Program.use();
    glBindVertexArray(m_Vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, cCnt * 6 * sizeof (point), points, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, cCnt * 6 * sizeof (uint32_t), data, GL_DYNAMIC_DRAW);

    glm::mat4 tmpmat = glm::mat4(1.0f);



    tmpmat = glm::scale(tmpmat, glm::vec3(sx, sy, 1.0f));

    //tmpmat = glm::translate(tmpmat, glm::vec3(x, y, 0.0f));

    tmpmat = tmpmat * _mat;

    glUniform1f(m_stepSize, 2 / sx);

    glUniform1i(m_tex, m_Font->m_TextureNumber);

    glUniformMatrix4fv(m_charMat, 1, GL_FALSE, glm::value_ptr(tmpmat));
    glDrawArrays(GL_TRIANGLES, 0, cCnt * 6);

    delete[] points;
    delete[] data;
    delete[] textO;
    //std::cout << "bla" << std::endl;

}

unsigned char* Print::getUcs4CharFromString(uint32_t *out, unsigned char *in) { //FIXME can overflow in buffer if last char contains malformed unicode!
    unsigned char in1 = *((unsigned char*) in);

    if (in1 < 0b11000000) {
        *out = in1;
        return in + 1;
    } else if (in1 < 0b11100000) {
        *out = (*(in + 1) & 0b00111111) | ((*(in) & 0b00011111) << 6);
        return in + 2;
    } else if (in1 < 0b11110000) {
        *out = (*(in + 2) & 0b00111111) | ((*(in + 1) & 0b00111111) << 6) | ((*(in) & 0b00001111) << 12);
        return in + 3;
    } else if (in1 < 0b11111000) {
        *out = (*(in + 3) & 0b00111111) | ((*(in + 2) & 0b00111111) << 6) | ((*(in + 1) & 0b00111111) << 12) | ((*(in) & 0b00000111) << 18);
        return in + 4;
    }




    return in + 1;
}

void Print::setScreenSize(glm::uvec2 size) {
    _screen = size;
    float ratio = (float) size.x / (float) size.y;
    _mat = glm::ortho(-(float) size.x / 2, (float) size.x / 2, -(float) size.y / 2, (float) size.y / 2, 1.0f, -1.0f);
}
