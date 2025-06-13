#include <glad/glad.h>

// NOTE: antiquated
typedef struct TexturedQuad{
    unsigned int VAO;
    unsigned int glTexture;
    unsigned int texWidth; // I don't like this
    unsigned int texHeight;
}TexturedQuad;

// Sets up textured quad VAO and texture id for rendering
void texturedQuadInit(TexturedQuad* texturedQuad, const char* texturePath){
    // Quad vertices and indices
    float vertices[] = {
        // positions    // texture coords
         0.5f,  0.5f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // VBO
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);
    // Positions vertex attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    // Tex coords vertex attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    // Generate gl texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Load bmp file
    BMPFile bmpFile;
    bmpLoadFromFile(&bmpFile, texturePath);
    // Load pixel data into gltexture (note: BGRA format for bmp images)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmpFile.width, bmpFile.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bmpFile.pixelBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set textured quad values
    texturedQuad->VAO = VAO;
    texturedQuad->glTexture = texture;
    texturedQuad->texWidth = bmpFile.width;
    texturedQuad->texHeight = bmpFile.height;

    bmpFree(&bmpFile);

}

// Renders textured quad (duh)
void texturedQuadRender(TexturedQuad* texturedQuad, unsigned int shaderProgram, Transform transform){
    glBindVertexArray(texturedQuad->VAO);
    glBindTexture(GL_TEXTURE_2D, texturedQuad->glTexture);
    
    // Applies transform
    shaderSetMat4(shaderProgram, "model", transformToMat4(transform));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}