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
    if (!window.GetGlfwWindow())
    {
        glfwTerminate();
        return -1; 
    }

    renderer.MakeContextCurrent(window);

    while (!window.ShouldClose())
    {
        renderer.Clear();

        renderer.SwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}