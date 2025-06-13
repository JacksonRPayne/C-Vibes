#include <GLFW/glfw3.h>
#define MAX_KEYS 1024

char keys[MAX_KEYS];


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keys[key] = action;
}
