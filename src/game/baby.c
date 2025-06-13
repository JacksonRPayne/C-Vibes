typedef struct Baby{
    Transform transform;
    Sprite sprite;
    float nextFrameTimer; // Temp animation testing 
}Baby;

Baby babyInit(){
    Baby baby;
    
    // Should be moved elsewhere tbh
    Texture texture = textureLoadFromBMP("res/textures/baby.bmp");
    baby.sprite = spriteInit(texture, 32, 32, 0, 0, 4);
    baby.transform = (Transform){.x=0, .y=0, .w = baby.sprite.width, .h= baby.sprite.height, .r=0};

    baby.nextFrameTimer = 0.2f;
    return baby;
}

void babyUpdate(Baby* baby, float dt){
    float speed = 300.0f;
    // Animation test
    baby->nextFrameTimer -= dt;
    if(baby->nextFrameTimer <=0){
        baby->sprite.costume += 1;
        if(baby->sprite.costume >= baby->sprite.costumeCount) baby->sprite.costume = 0;
        baby->nextFrameTimer = 0.2f;
    }
    if(keys[GLFW_KEY_RIGHT]){
        baby->transform.x += speed * dt;
    }
    else if(keys[GLFW_KEY_LEFT]){
        baby->transform.x -= speed * dt;
    }
    if(keys[GLFW_KEY_UP]){
        baby->transform.y += speed * dt;
    }
    else if(keys[GLFW_KEY_DOWN]){
        baby->transform.y -= speed * dt;
    }

}
