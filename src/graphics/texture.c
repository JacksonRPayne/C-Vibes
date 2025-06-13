// Holds a gl texture id and a width and height
typedef struct Texture{
    unsigned int id;
    unsigned int width;
    unsigned int height;
}Texture;

// Creates a gl texture for bmp file and returns a texture struct
Texture textureLoadFromBMP(const char* path){
    // Load bmp file
    BMPFile bmp;
    bmpLoadFromFile(&bmp, path);

    // Generate gl texture
    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    // Texture parameters (HARDCODED FOR NOW)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load pixel data into gltexture (note: BGRA format for bmp images)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.width, bmp.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bmp.pixelBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Construct struct
    Texture texture = {.id = texId, .width = bmp.width, .height = bmp.height };
    bmpFree(&bmp);

    return texture;
}

// Somewhat unnecessary wrapper but whatever
void textureUse(Texture texture){
    glBindTexture(GL_TEXTURE_2D, texture.id);
}

