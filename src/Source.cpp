#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        cout << "glew error";

    cout << glGetString(GL_VERSION) << endl;
    
    GLfloat tri[] = {
        -0.5f, -0.5f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.5f,
        0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,
        0.0f, 0.0f, 1.0f,
        -0.4f, 0.5f,
        0.0f, 1.0f, 0.0f,
        -0.3f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    GLushort ind[] = { // indices of vertices
        0, 1, 2,
        0, 3, 4
    };

    GLuint bufferID;
    glGenBuffers(1, &bufferID); // creating a buffer, storing uid inside bufferID
    glBindBuffer(GL_ARRAY_BUFFER, bufferID); // binding uid to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW); // initializing buffer with data
    glEnableVertexAttribArray(0); // vertex position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(1); // vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char *)(sizeof(float) * 2));

    GLuint indBufferID;
    glGenBuffers(1, &indBufferID); // buffer of vertex indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
