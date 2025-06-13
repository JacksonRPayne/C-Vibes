#include <stdio.h>
#include <GLFW/glfw3.h>

void onWindowResize(GLFWwindow* window, int width, int height){
    // TODO: fixed aspect ratio
    glViewport(0, 0, width, height);
}

GLFWwindow* initializeWindow(){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        printf("ERROR: Glfw init failed");
        return NULL;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 360, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("ERROR: glfw window failed to create");
        return NULL;
    }
    
    // Specify opengl version 3.3s
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Set callbacks
    glfwSetWindowSizeCallback(window, onWindowResize);
    glfwSetKeyCallback(window, keyCallback);

    // Setup openGL context
    if(!gladLoadGL()){
        printf("ERROR: Glad failed to load");
        return NULL;
    }
    
    glViewport(0,0,640, 360);
    glClearColor(0.95f, 0.8f, 1.0f, 1.0f);

    // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    return window;
}

