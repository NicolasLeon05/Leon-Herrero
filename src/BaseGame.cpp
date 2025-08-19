#include <GLFW/glfw3.h>

#include "Window.h"

int main(void)
{
    Window window = Window(640, 480, "Engine");

    GLFWwindow* gflwWindow;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window.CreateWindow();
    if (!window.GetGlfwWindow())
    {
        glfwTerminate();
        return -1; 
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window.GetGlfwWindow());

    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.GetGlfwWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}