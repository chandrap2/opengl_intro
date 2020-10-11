#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h";

using namespace std;

//const char* vertShader =
//    "#version 430\r\n"
//    ""
//    "in layout(location=0) vec2 position;"
//    "in layout(location=1) vec3 inColor;"
//    ""
//    "out vec3 outColor;"
//    ""
//    "void main()"
//    "{"
//    "   gl_Position = vec4(position, 0.0, 1.0);"
//    "   outColor = inColor;"
//    "}";
//
//const char* fragShader =
//    "#version 430\r\n"
//    ""
//    "in vec3 outColor;"
//    ""
//    "out vec4 color;"
//    ""
//    "void main()"
//    "{"
//    "   color = vec4(outColor, 0.0);"
//    "}";

// initializing vertex buffers
void initBuffers() {
    GLfloat tri[] = {
        -0.5f, -0.5f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.5f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.2f,
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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

    GLuint indBufferID;
    glGenBuffers(1, &indBufferID); // buffer of vertex indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
}

// initializing and linking shaders
void initShaders() {
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    Shader vertShader("vertShader.txt");
    Shader fragShader("fragShader.txt");
    const char* codeAdapter[1];
    codeAdapter[0] = vertShader.getShader();
    glShaderSource(vertShaderID, 1, codeAdapter, 0);
    codeAdapter[0] = fragShader.getShader();
    glShaderSource(fragShaderID, 1, codeAdapter, 0);

    glCompileShader(vertShaderID);
    glCompileShader(fragShaderID);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);
    glUseProgram(programID);
}

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

    initBuffers();
    initShaders();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
