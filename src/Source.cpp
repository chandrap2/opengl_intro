#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <iostream>

#include "Shader.h";
#include "Model.h";
#include "Camera.h";

using namespace std;
using glm::vec3;
using glm::mat4;

GLuint programID;
float camSpeed = 2.0f;

// initializing vertex buffers
void initBuffers(Model& m) {
    const int vertSize = m.getVertSize();
    //const int indSize = m.getIndSize();
    GLfloat* tri = new GLfloat[vertSize];
    //GLshort* ind = new GLshort[indSize];
    //m.setVerts(tri, ind);
    m.setVerts(tri);

    GLuint bufferID;
    glGenBuffers(1, &bufferID); // creating a buffer, storing uid inside bufferID
    glBindBuffer(GL_ARRAY_BUFFER, bufferID); // binding uid to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float), tri, GL_STATIC_DRAW); // initializing buffer with data
    glEnableVertexAttribArray(0); // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glEnableVertexAttribArray(1); // vertex normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

    //GLuint indBufferID;
    //glGenBuffers(1, &indBufferID); // buffer of vertex indices
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufferID);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize * sizeof(GLshort), ind, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind2), ind2, GL_STATIC_DRAW);

    delete [] tri;
    //delete [] ind;
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

    programID = glCreateProgram();
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);

    int success;
    char log[512];

    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShaderID, 512, NULL, log);
        cout << "vert error: " << endl << log << endl;
    }
    
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShaderID, 512, NULL, log);
        cout << "frag error: " << endl << log << endl;
    }
    
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, log);
        cout << "prog link error: " << endl << log << endl;
    }

    glUseProgram(programID);


    //mat4 trans = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
    mat4 trans = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.0f));
    mat4 rotate = glm::rotate(mat4(1.0f), 3.1415f * .25f, vec3(1.0f, 0.0f, 1.0f));
    //mat4 rotate = glm::rotate(mat4(1.0f), 0.1f, vec3(1.0f, 1.0f, 0.0f));
    //mat4 transform = trans * rotate;
    mat4 transform = trans * rotate;
    vec3 color(1.0f, 0.0f, 0.0f);
    vec3 lightPos(0.0f, 0.0, 0.0f);

    GLint transPos = glGetUniformLocation(programID, "transform");
    glUniformMatrix4fv(transPos, 1, GL_FALSE, &transform[0][0]);
    GLint rotPos = glGetUniformLocation(programID, "rotation");
    glUniformMatrix4fv(rotPos, 1, GL_FALSE, &rotate[0][0]);
    GLint colorPos = glGetUniformLocation(programID, "modelColor");
    glUniform3fv(colorPos, 1, &color.r);
    GLint lightP_Pos = glGetUniformLocation(programID, "lightPos");
    glUniform3fv(lightP_Pos, 1, &lightPos.x);
}

void processInput(GLFWwindow* window, Camera& cam, float dt) {
    float currSpeed = camSpeed * dt;

    if (glfwGetKey(window, GLFW_KEY_W)) cam.translate(cam.front * currSpeed);
    if (glfwGetKey(window, GLFW_KEY_S)) cam.translate(cam.front * -currSpeed);
    if (glfwGetKey(window, GLFW_KEY_A)) cam.translate(cam.right * -currSpeed);
    if (glfwGetKey(window, GLFW_KEY_D)) cam.translate(cam.right * currSpeed);
    if (glfwGetKey(window, GLFW_KEY_LEFT)) cam.rotate(currSpeed * 3, cam.up);
    if (glfwGetKey(window, GLFW_KEY_RIGHT)) cam.rotate(-currSpeed * 3, cam.up);
    if (glfwGetKey(window, GLFW_KEY_UP)) cam.rotate(currSpeed * 3, cam.right);
    if (glfwGetKey(window, GLFW_KEY_DOWN)) cam.rotate(-currSpeed * 3, cam.right);
}

int main(void)
{
    GLFWwindow* window;
    Camera cam;

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
    cout << glGetString(GL_VERSION) << endl << endl;


    //Model m1("Cube.txt");
    Model m1("Cube2.txt");

    initBuffers(m1);
    initShaders();
    
    glEnable(GL_DEPTH_TEST);

    float lastTime 
        = glfwGetTime();
    float dt, currSpeed;
    float currAngle = 0.0f;
    
    GLint projPos = glGetUniformLocation(programID, "projection");
    GLint cameraP_Pos = glGetUniformLocation(programID, "cameraPos");
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        dt = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();
        processInput(window, cam, dt);

        mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, .1f, 100000.0f) * cam.look();
        glUniformMatrix4fv(projPos, 1, GL_FALSE, &proj[0][0]);
        glUniform3fv(cameraP_Pos, 1, &cam.pos.x);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ///* Swap front and back buffers */  
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
