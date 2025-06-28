#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<stdbool.h>

bool line_mode = false;

float vertices[] = {
    -0.17f, 0.6f, 0.0f, //top right body
    -0.17f, -0.6f, 0.0f, //bottom right body
    -0.3f, -0.6f, 0.0f,  //bottom left body
    -0.3f, 0.6f, 0.0f, //top left body

    0.3f, 0.6f, 0.0f, //top right upper
    0.3f, 0.45f, 0.0f, //bottom right upper
    -0.2f, 0.45f, 0.0f,  //bottom left upper
    -0.2f, 0.6f, 0.0f, //top left upper

    0.2f, 0.2f, 0.0f, //top right down
    0.2f, 0.05f, 0.0f, //bottom right down
    -0.2f, 0.05f, 0.0f,  //bottom left down
    -0.2f, 0.2f, 0.0f //top left down
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3,

    4, 5, 7,
    5, 6, 7,

    8, 9, 11,
    9, 10, 11
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (key == GLFW_KEY_W && action == GLFW_PRESS){
        if (!line_mode){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            line_mode = true;
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            line_mode = false;
        }
        
    }
    
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

    GLFWwindow *window = glfwCreateWindow(800, 600, "Respect", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Error in glad");
        return -1;
    }

    GLuint vertexShader, fragmentShader, shaderProgram;
    compilarVertexShader(&vertexShader);
    compilarFragmentShader(&fragmentShader, fragmentShaderSource);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLuint VAO, VBO, EBO;


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    glEnableVertexAttribArray(0);


    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    

    while(!glfwWindowShouldClose(window)){
        
        glfwSetKeyCallback(window, key_callback);

        glClear(GL_COLOR_BUFFER_BIT);

        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}