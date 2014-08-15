#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "gl/Program.h"
#include "font/Print.h"
#


int main(){
    std::setlocale(LC_ALL, "en_US.UTF-8");
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(800, 600, "test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    glewInit();
    Shader* fs = new Shader("res/shader/fragment.c", true, GL_FRAGMENT_SHADER);
    Shader* vs = new Shader("res/shader/vertex.c", true, GL_VERTEX_SHADER);
    Program* p = new Program();
    p->attach(fs);
    p->attach(vs);
    p->build();
    p->use();
    TextureManager* tm = new TextureManager();
    Font font(512, "res/font/DroidSans.woff", 32, tm);
    Print print(&font);
    //print.set(&font, "res/shader/fontVertex.c", "res/shader/fontFragment.c");
    print.setScreenSize(Vec2<unsigned int>(800, 600));
    float vert[] = { -.5f, -.5f, 
        .5f, -.5f,
        .5f, .5f,
        -.5f, .5f, };
    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        print.printfAt(-1.0f, -0.45f, 0.15f, 0.15f, u8"1234567890hallo");
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	
    std::cout << "Hello World. I'm Peach." << std::endl;
    
    return 0;
}

void windowSizeCallback(GLFWwindow* win, int w, int h)
{
    
}