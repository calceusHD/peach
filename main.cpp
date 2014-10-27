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
    TileRenderer *tr;
    Vec2<unsigned int> screen;
    public:
    
        Main() 
        {
            screen = Vec2<unsigned int>(800, 600);
            std::setlocale(LC_ALL, "en_US.UTF-8");
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            GLFWwindow* window = glfwCreateWindow(screen.x, screen.y, "test", nullptr, nullptr);
            if (window == nullptr)
            {
                printf("cant create window");
                return;
            }
            
            glfwSetWindowSizeCallback(window, windowSizeCallback);
            glfwSetKeyCallback(window, keyCallback);
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
            print->setScreenSize(screen);
            glm::vec2* vert = new glm::vec2[1024];
            uint32_t vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            uint32_t vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glEnableVertexAttribArray(0);
            glBufferData(GL_ARRAY_BUFFER, 1024 * sizeof(glm::vec2), vert, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
            glEnable(GL_BLEND);
            glfwSetWindowUserPointer(window, this);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            double cx, cy;
            double px, py;
            int cnt = 0;
            
            
            tr = new TileRenderer();
            tr->setScreenSize(screen);
            Tile t;
            t.addStroke(new Stroke((glm::vec2*)new float[8]{-0.2f, 0.1f, 0.3f, 0.0f, -0.2f, -0.01f}, 3, 0.08f));
            double time, timeo;
            bool click = false, clickPrev = false;
            glfwSwapInterval(0);
            while(!glfwWindowShouldClose(window))
            {
                timeo = time;
                time = glfwGetTime();
                glClear(GL_COLOR_BUFFER_BIT);
                
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
                    glfwGetCursorPos(window, &cx, &cy);

                    if (px != cx && py != cy && cnt < 1024)
                    {
                        //vert[cnt] = glm::vec2(cx, -cy) / 500.0f - glm::vec2(screen.x, -screen.y) / 1000.0f;
                        vert[cnt] = glm::vec2((cx / screen.x - 0.5f) * 2.0f * screen.x / 1000.0f,
                            -(cy / screen.y - 0.5f) * 2.0f * screen.y / 1000.0f);
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
                    t.addStroke(new Stroke(vert, cnt, 0.02f));
                }
                //glDrawArrays(GL_LINE_STRIP, 0, cnt);
                tr->renderTile(&t);
                print->printfAt(-1.0f, 0.1f, 30.0f, 30.0f, u8"x:%f, y:%f", cx, cy);
                print->printfAt(-300.0f, 100.0f, 16.0f, 16.0f, u8"Fps:%f", 1/(time-timeo));
                glfwSwapBuffers(window);
                glfwPollEvents();
                
            }


            std::cout << "Hello World. I'm Peach." << std::endl;



        }



    static void windowSizeCallback(GLFWwindow* win, int w, int h)
    {
        glViewport(0, 0, w, h);
        
        Main* main = (Main*)glfwGetWindowUserPointer(win);
        main->screen = Vec2<unsigned int>(w, h);
        main->print->setScreenSize(main->screen);
        main->tr->setScreenSize(main->screen);
        
    }
    
    static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods) {
        Main* main = (Main*)glfwGetWindowUserPointer(win);
        if (key == GLFW_KEY_F9 && action == GLFW_PRESS)
            main->tr->setDebug(!main->tr->getDebug());
        
        
    }
};


int main(){
    new Main();
}
