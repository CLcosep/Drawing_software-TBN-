#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// compiling a shader
const char *vertextShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


int main() {

    // std::cout << "HelloWorld!" << std::endl;
    // GLFWwindow* window;

    // if (!glfwInit()){
    //     return -1;
    // }

    // window = glfwCreateWindow(640, 480, "Window!", NULL, NULL);
    // glfwMakeContextCurrent(window);

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    //     std::cout << "Couldn't load opengl" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }

    // glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    // while(!glfwWindowShouldClose(window)){
    //     glfwPollEvents();
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     glfwSwapBuffers(window);
    // }

    // glfwTerminate();


    // -- glfw: init and config
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // -- window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OPENGL BUANG", NULL, NULL); //declare window object
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // -- glad: load all OpenGL func ptr
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // glViewport(0, 0, 800, 600); //tell opengl the size of the rendering window 
    // framebuffer_size_callback(window, 800, 600);

    // -- build and comp shader prog
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);
    glCompileShader(vertexShader);
    // check vertex shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    // shader program obj
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    // check shader program obj
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error::SHADER::SHADERPROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glDeleteProgram(vertexShader);
    glDeleteProgram(fragmentShader);

    // setup vertex data and config vertex attributes
    // float vertices[] = {
    //     // 0.0f, 0.433f, 0.0f,     //top right
    //     //  0.5f, -0.433f, 0.0f,     //bottom right
    //     // -0.5f, -0.433f, 0.0f,     //bottom left
    //     // 0.0f, -0.433f,  0.0f      //top left

    //      -0.9f, -0.5f, 0.0f,  // left 
    //     -0.0f, -0.5f, 0.0f,  // right
    //     -0.45f, 0.5f, 0.0f,  // top 
    //     // second triangle
    //      0.0f, -0.5f, 0.0f,  // left
    //      0.9f, -0.5f, 0.0f,  // right
    //      0.45f, 0.5f, 0.0f
    // };
    // unsigned int indices[] = {
    //     0, 2, 3, //first triangle
    //     0, 3, 1 // second triangle
    // };

    float squareVertices[] = {
        0.8f, 0.5f, 0.0f,    //topright
        0.8f, -0.5f, 0.0f,   //bottom right
        0.2f, -0.5f, 0.0f,  //bottom left
        0.2f, 0.5f, 0.0f    //topleft
    };
    unsigned int squareIndices[] = {
        0, 1, 3, //firt tria
        1, 2, 3  //second tria
    };  

    float triangleVertices[] = {
        -0.2f, -0.5f, 0.0f, //bottom right
        -0.8f, -0.5f, 0.0f, //bottom left
        -0.5f, 0.5f, 0.0f   //top
    };
    // vertex buffer object
    // unsigned int VBO, VAO, EBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    // // bind vertex array object (VAO) first then bind vertex buffer then confiugre vertex attributes
    // glBindVertexArray(VAO);
    
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glBindVertexArray(0);

    unsigned int VBO[2], VAO[2], EBO;
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    // wirframe polygon
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)) {

        // input
        processInput(window);

        // rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //state-setting
        glClear(GL_COLOR_BUFFER_BIT);           //state-using

        // // draw first triangle
        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // deallocate after 
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);

    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteBuffers(1, &EBO);

    glDeleteVertexArrays(1, &VAO[1]);
    glDeleteBuffers(1, &VBO[1]);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool wireframe = false;
bool PKeyPress = false;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    //     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // else 
    //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    bool pDown = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
    
    if (pDown && !PKeyPress) {
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }
    PKeyPress = pDown;
}