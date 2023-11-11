#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES

static void glfwError(int id, const char *description);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
bool esc = true;
int main()
{

    float vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};
   glfwSetErrorCallback(&glfwError);
if (!glfwInit())
{
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);
if (!window)
{
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
}

glfwMakeContextCurrent(window);

// Initialize Glad (after creating GLFW context)
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize Glad\n");
    return -1;
}

glViewport(0, 0, 800, 600);


    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
        
        processInput(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static void glfwError(int id, const char *description)
{
    std::cout << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    std::cout << "RESIZING TO " << width << " " << height << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "Pressed escape,leaving..." << std::endl;
        esc = false;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
    {
    }
}
