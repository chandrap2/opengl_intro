#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h";
#include "Model.h";

using namespace std;

// initializing vertex buffers
void initBuffers(Model& m) {
    const int vertSize = m.getVertSize();
    const int indSize = m.getIndSize();
    GLfloat* tri = new GLfloat[vertSize];
    GLshort* ind = new GLshort[indSize];
    m.setVerts(tri, ind);

    GLuint bufferID;
    glGenBuffers(1, &bufferID); // creating a buffer, storing uid inside bufferID
    glBindBuffer(GL_ARRAY_BUFFER, bufferID); // binding uid to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float), tri, GL_STATIC_DRAW); // initializing buffer with data
    //glBufferData(GL_ARRAY_BUFFER, sizeof(tri2), tri2, GL_STATIC_DRAW); // initializing buffer with data
    glEnableVertexAttribArray(0); // vertex position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(1); // vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

    GLuint indBufferID;
    glGenBuffers(1, &indBufferID); // buffer of vertex indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize * sizeof(GLshort), ind, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind2), ind2, GL_STATIC_DRAW);
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

    Model m1("model - Copy.txt");

    initBuffers(m1);
    initShaders();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        ///* Swap front and back buffers */
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
