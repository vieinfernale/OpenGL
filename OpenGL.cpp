#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    /* Initialization of GLFW */
    if (!glfwInit())
    {
        return -1;
    }

    /* Create a Window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /* Initialization of GLEW */
    if (glewInit() != GLEW_OK)
    {
        std::cout << glewGetErrorString(glewInit()) << std::endl;
    }

    /* OpenGL Version */
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.25f, 0.5f);
        glVertex2f(0.0f, 0.0f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}