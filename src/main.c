#include "unityBuild.h"
// Unity build ftw


int main(void)
{
    GLFWwindow* window = initializeWindow();
    
    TexturedQuad texturedQuad;
    texturedQuadInit(&texturedQuad, "res/textures/test.bmp");

    Baby baby = babyInit();

    unsigned int shaderProgram = shaderCompile("res/shaders/default.vert", "res/shaders/default.frag");

    glUseProgram(shaderProgram);

    Transform camera = {.x=320.0f, .y=180.0f, .w=2.0f, .h=2.0f, .r=0.0f};
    mat4 proj = mat4Ortho(0.0f, 640.0f, 0.0f, 360.0f, -1.0f, 1.0f);
    shaderSetMat4(shaderProgram, "projection", proj);

    Transform t1 = { 0.0f, 0.0f, 100.0f, 100.0f, 0.0f};
    
    float dt = 0.0f;
    float currFrame = 0.0f;
    float lastFrame = 0.0f;

    int tileMap[20*2] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
    Texture tex = textureLoadFromBMP("res/textures/tiles.bmp");
    Sprite tileSprite = spriteInit(tex, 8,8, 0, 8, 2);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Delta time
        currFrame = (float)glfwGetTime();
        dt = currFrame - lastFrame;
        lastFrame = currFrame;

        babyUpdate(&baby, dt);

        //printf("%d", keys[GLFW_KEY_SPACE]);
        float speed = 300.0f;


        if(keys[GLFW_KEY_D]){
            camera.x -= speed * dt;
        }
        else if(keys[GLFW_KEY_A]){
            camera.x += speed * dt;
        }
        if(keys[GLFW_KEY_W]){
            camera.y -= speed * dt;
        }
        else if(keys[GLFW_KEY_S]){
            camera.y += speed * dt;
        }
        
        shaderSetMat4(shaderProgram, "view", transformToMat4(camera));


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLenum error;
        while(error = glGetError()){
            printf("GL ERROR: %d", error);
        }
        tileMapRenderer(20,2, tileMap, shaderProgram, tileSprite);
        //Transform t =  {0.0f, 0.0f, 16.0f * WORLD_SCALE,16.0f * WORLD_SCALE, 0.0f};
        //spriteRender(tileSprite,t, shaderProgram);
        //texturedQuadRender(&texturedQuad, shaderProgram, t1);
        spriteRender(baby.sprite, baby.transform, shaderProgram);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

