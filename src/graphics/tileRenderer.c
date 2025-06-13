#define TILE_SIZE 8.0f

typedef struct TileRenderer{
    unsigned int VAO;
    // Holds all quad data
    float* quadBuffer;
    // Holds current index in quad buffer
    float* quadBufferPtr;
    Texture atlas;
}TileRenderer;


int tileMapGetIndex(int x, int y, int tsWidth){
    return x + y * tsWidth;
}

// TODO: remove shader param
void tileRender(int tile, float x, float y, unsigned int shaderProgram, Sprite sprite){
    Transform t = {.x=x, .y=y, .w=TILE_SIZE , .h= TILE_SIZE, .r=0};
    sprite.costume = tile-1;
    spriteRender(sprite, t, shaderProgram);
}

void tileMapRenderer(int width, int height, int* tileSet, unsigned int shaderProgram, Sprite sprite){

    for(int h = 0; h<height; h++){
        float currY = height * (int)TILE_SIZE - h * (int)TILE_SIZE;
        for(int w = 0; w<width; w++){
            int tile = tileSet[tileMapGetIndex(w, h, width)];
            if(tile==0) continue;

            float currX = w * (int)TILE_SIZE;
            tileRender(tile, currX, currY, shaderProgram, sprite);
        }
    }

}


