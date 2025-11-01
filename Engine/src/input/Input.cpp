#include "Input.h"

std::unordered_map<int, bool> Input::s_KeyCurrent;
std::unordered_map<int, bool> Input::s_KeyPrevious;

void Input::Init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, KeyCallback);
}

void Input::Update()
{
    s_KeyPrevious = s_KeyCurrent;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        s_KeyCurrent[key] = true;
    else if (action == GLFW_RELEASE)
        s_KeyCurrent[key] = false;
}

bool Input::IsKeyPressed(Key key)
{
    int k = static_cast<int>(key);
    return s_KeyCurrent[k] && !s_KeyPrevious[k];
}

bool Input::IsKeyReleased(Key key)
{
    int k = static_cast<int>(key);
    return !s_KeyCurrent[k] && s_KeyPrevious[k];
}

bool Input::IsKeyDown(Key key)
{
    return s_KeyCurrent[static_cast<int>(key)];
}

bool Input::IsKeyUp(Key key)
{
    return !s_KeyCurrent[static_cast<int>(key)];
}
