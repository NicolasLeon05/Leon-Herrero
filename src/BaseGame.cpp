#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Renderer.h"

int main(void)
{
    Window window = Window(640, 480, "Engine");

    Renderer renderer;

    if (!glfwInit())
        return -1;

    window.CreateWindow();

    renderer.MakeContextCurrent(window);

    glewInit();

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 
        vertices, GL_STREAM_DRAW);

    while (!window.ShouldClose())
    {
        renderer.Clear();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        renderer.SwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}