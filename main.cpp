#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "gl/Program.h"
#include "font/Print.h"
#include "TileRenderer.h"
#include "Tile.h"
#include "Stroke.h"

#define mouseDown click && !clickPrev
#define mouseUp !click && clickPrev
#define mousePressed click

class Main {
    
    Print* print;
    Font* font;
    TextureManager * tm;
    public:
    
        Main() 
        {
            int width = 800, height = 600;
            std::setlocale(LC_ALL, "en_US.UTF-8");
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            GLFWwindow* window = glfwCreateWindow(width, height, "test", nullptr, nullptr);
            if (window == nullptr)
            {
                printf("cant create window");
                return;
            }
            
            glfwSetWindowSizeCallback(window, windowSizeCallback);
            glfwMakeContextCurrent(window);
            glewExperimental = true;
            glewInit();
            printf("%s\n", glGetString(GL_VERSION));
            Shader* fs = new Shader("res/shader/fragment.c", true, GL_FRAGMENT_SHADER);
            Shader* vs = new Shader("res/shader/vertex.c", true, GL_VERTEX_SHADER);
            Program* p = new Program();
            p->attach(fs);
            p->attach(vs);
            p->build();
            p->use();
            tm = new TextureManager();
            font = new Font(512, "res/font/DroidSans.woff", 32, tm);
            print = new Print(font);
            //print.set(&font, "res/shader/fontVertex.c", "res/shader/fontFragment.c");
            print->setScreenSize(Vec2<unsigned int>(width, height));
            float* vert = new float[2048];
            uint32_t vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            uint32_t vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glEnableVertexAttribArray(0);
            glBufferData(GL_ARRAY_BUFFER, 2048 * sizeof(float), vert, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
            glEnable(GL_BLEND);
            glfwSetWindowUserPointer(window, this);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            int cx, cy;
            int px, py;
            int cnt = 0;
            
            
            TileRenderer tr;
            Tile t;
            t.addStroke(new Stroke(new float[8]{-0.7f, 0.7f, 0.9f, 0.9f, 0.3f, -0.7f, -0.5f, -0.5f}, 4, 0.08f));
            
            bool click = false, clickPrev = false;
            
            while(!glfwWindowShouldClose(window))
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                print->printfAt(0.0f, -0.0f, 100.0f, 100.0f, u8"1234567890hallo");
                glBindVertexArray(vao);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                clickPrev = click;
                click = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
                if (mouseDown)
                {
                    memset(vert, 0, 2048 * sizeof(float));
                    cnt = 0;
                }
                if (mousePressed)
                {
                    double xpos, ypos;
                    glfwGetCursorPos(window, &xpos, &ypos);
                    cx = floor(xpos);
                    cy = floor(ypos);
                    if (px != cx && py != cy && cnt < 1024)
                    {
                        vert[cnt * 2 + 0] = ((float)cx / width - 0.5f) * 2.0f;
                        vert[cnt * 2 + 1] = -((float)cy / height - 0.5f) * 2.0f;
                        cnt ++;
                        px = cx;
                        py = cy;

                        glBufferData(GL_ARRAY_BUFFER, 2048 * sizeof(float), vert, GL_DYNAMIC_DRAW);
                    }
                }
                
                p->use();
                //glBufferData(GL_ARRAY_BUFFER, 2048 * sizeof(float), vert, GL_DYNAMIC_DRAW);
                glDrawArrays(GL_LINE_STRIP, 0, cnt);
                if (mouseUp)
                {
                    t.addStroke(new Stroke(vert, cnt, 0.002f));
                }
                //glDrawArrays(GL_LINE_STRIP, 0, cnt);
                tr.renderTile(&t);
                print->printfAt(-1.0f, 0.1f, 30.0f, 30.0f, u8"x:%i, y%i", cx, cy);
                glfwSwapBuffers(window);
                glfwPollEvents();
                
            }


            std::cout << "Hello World. I'm Peach." << std::endl;



        }



    static void windowSizeCallback(GLFWwindow* win, int w, int h)

    {
        glViewport(0, 0, w, h);
        ((Main*)glfwGetWindowUserPointer(win))->print->setScreenSize(Vec2<unsigned int>(w, h));
    }
};


int main(){
    new Main();
}
