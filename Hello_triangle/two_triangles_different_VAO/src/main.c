#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<stdbool.h>

float vertices[] = {
    0.0f, -0.4f, 0.0f,
    0.8f, -0.4f, 0.0f,
    0.4f,  0.4f, 0.0f
};

float vertices2[] = {
    -0.8f, -0.4f, 0.0f,
    0.0f, -0.4f, 0.0f,
    -0.4f, 0.4f, 0.0f
};

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"

    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"

    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void compilarVertexShader(GLuint *vertexShader){
    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(*vertexShader);
}

void compilarFragmentShader(GLuint *fragmentShader, const char *source){
    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(*fragmentShader, 1, &source, NULL);
    glCompileShader(*fragmentShader);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Two triangles OpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Error in glad");
        return -1;
    }

    GLuint vertexShader, fragmentShader, fragmentShader2, shaderProgram, shaderProgram2;
    compilarVertexShader(&vertexShader);
    compilarFragmentShader(&fragmentShader, fragmentShaderSource);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    compilarFragmentShader(&fragmentShader2, fragmentShaderSource2);
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    GLuint VAO, VAO2, VBO, VBO2;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glGenVertexArrays(2, &VAO2);
    glGenBuffers(2, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);


    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){
        
        glfwSetKeyCallback(window, key_callback);

        glClear(GL_COLOR_BUFFER_BIT);

        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}