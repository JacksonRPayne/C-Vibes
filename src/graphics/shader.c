#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Create OpenGL shader from source files
unsigned int shaderCompile(const char* vertPath, const char* fragPath){

    // Open vertex and fragment shader files
    FILE* vertFile = fopen(vertPath, "rb");
    if(vertFile == NULL) printf("ERROR: vertex shader could not be found. Path: %s", vertPath);
    
    FILE* fragFile = fopen(fragPath, "rb");
    if(fragFile == NULL) printf("ERROR: fragment shader could not be found. Path: %s", fragPath);

    // Find length of files
    size_t vertFileSize = 0;
    size_t fragFileSize = 0;

    fseek(vertFile, 0L, SEEK_END);
    vertFileSize = ftell(vertFile);
    rewind(vertFile);

    fseek(fragFile, 0L, SEEK_END);
    fragFileSize = ftell(fragFile);
    rewind(fragFile);

    // Allocate buffers for file contents
    char vertBuffer[vertFileSize+1];
    char fragBuffer[fragFileSize+1];
    
    // Load data into buffers
    fread(vertBuffer, vertFileSize, 1, vertFile);
    fread(fragBuffer, fragFileSize, 1, fragFile);

    vertBuffer[vertFileSize] = '\0'; // oh boy
    fragBuffer[fragFileSize] = '\0';

    const char* vertSource = vertBuffer;
    const char* fragSource = fragBuffer;


    // Create shaders with OpenGL
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load source code buffers
    glShaderSource(vertexShader, 1, &vertSource, NULL);   
    glShaderSource(fragmentShader, 1, &fragSource, NULL);

    // Compile and error check
    int success;
    char infoLog[512];

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR: Vertex shader failed compilation: \n %s", infoLog);
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR: Fragment shader failed compilation: \n %s", infoLog);
    }

    // Create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attatch and link shaders into program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Linking error check
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR: Shader link error: \n %s", infoLog);
    }
    // Clean up shader source
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void shaderSetMat4(unsigned int shaderProgram, const char* uniformName, mat4 mat){
    glUseProgram(shaderProgram);
    unsigned int uniformLoc = glGetUniformLocation(shaderProgram, uniformName);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat.elements);
}

void shaderSetVec2(unsigned int shaderProgram, const char* uniformName, float x, float y){
    glUseProgram(shaderProgram);
    unsigned int uniformLoc = glGetUniformLocation(shaderProgram, uniformName);
    glUniform2f(uniformLoc, x, y);
}