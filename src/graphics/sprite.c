// Holds texture and subtexture data of an animated sprite
// A sprite is essentially an animatable subtexture?  
typedef struct Sprite
{
    // For rendering 
    unsigned int VAO;
    // The texture that contains the sprite
    Texture texture;
    // Width and height of the tiles containing the sprite and animated frames
    unsigned int width; 
    unsigned int height;
    // Pixel offset for start of sprite (NOTE: stored just for funsies)
    int pixOffsetX;
    int pixOffsetY;
    // Current animated frame the sprite is on (scratch reference :3)
    int costume;
    int costumeCount;
} Sprite;


// Sets up buffers for sprite and initializes its members
Sprite spriteInit(Texture texture, unsigned int width, unsigned int height, int pixOffsetX, int pixOffsetY, int costumeCount){
    // Initialize sprite fields
    Sprite sprite;
    sprite.VAO = 0;
    sprite.texture = texture;
    sprite.width = width;
    sprite.height = height;
    sprite.pixOffsetX = pixOffsetX;
    sprite.pixOffsetY = pixOffsetY;
    sprite.costume = 0;
    sprite.costumeCount = costumeCount;

    // Convert pixel values to normalized texCoord values
    float texOffsetX = (float) pixOffsetX / (float) texture.width;
    float texOffsetY = (float) pixOffsetY / (float) texture.height;
    float spWidth = (float) width / (float) texture.width;
    float spHeight = (float) height / (float) texture.height;

    float minX = texOffsetX;
    float maxX = texOffsetX + spWidth;
    float minY = texOffsetY;
    float maxY = texOffsetY + spHeight;

    // Quad vertices and indices
    float vertices[] = {
        // positions    // texture coords
         0.5f,  0.5f,   maxX, maxY,   // top right
         0.5f, -0.5f,   maxX, minY,   // bottom right
        -0.5f, -0.5f,   minX, minY,   // bottom left
        -0.5f,  0.5f,   minX, maxY    // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // VAO
    glGenVertexArrays(1, &sprite.VAO);
    glBindVertexArray(sprite.VAO);
    
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


    return sprite;
}

// Renders a fucking sprite
void spriteRender(Sprite sprite, Transform transform, unsigned int shaderProgram){
    glBindVertexArray(sprite.VAO);
    textureBind(sprite.texture);

    shaderSetMat4(shaderProgram, "model", transformToMat4(transform));
    // Applies animation frame
    float texOffsetX = ((float)sprite.width / (float)sprite.texture.width) * (float)sprite.costume;
    shaderSetVec2(shaderProgram, "texCoordOffset", texOffsetX, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
