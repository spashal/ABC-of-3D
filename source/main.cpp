int globalRotn = 0;
#include "main.h"
#include "timer.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
char shapeChosen;
Ball ball1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angleY = 0;
float camera_rotation_angleZ = 0;
float camera_rotation_angleX = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*(cos(camera_rotation_angleY*M_PI/180.0f) * cos(camera_rotation_angleZ*M_PI/180.0f)), 5*(sin(camera_rotation_angleZ*M_PI/180.0f)), 5*(sin(camera_rotation_angleY*M_PI/180.0f) * cos(camera_rotation_angleZ*M_PI/180.0f)) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(0, 1, 0);
        // glm::vec3 up (cos(camera_rotation_angleX*M_PI/180.0f), sin(camera_rotation_angleX*M_PI/180.0f)*sin(camera_rotation_angleZ*M_PI/180.0f), cos(camera_rotation_angleZ*M_PI/180.0f));
   
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (left) {
        // Do something
    }
}

void tick_elements() {
    // ball1.tick();
    if(globalRotn == 1)
        camera_rotation_angleY += 1;
    else if(globalRotn == 2)
        camera_rotation_angleY -= 1;
    else if(globalRotn == 3)
        camera_rotation_angleZ += 1;
    else if(globalRotn == 4)
        camera_rotation_angleZ -= 1;
    else if(globalRotn == 5)
        camera_rotation_angleX += 1;
    else if(globalRotn == 6)
        camera_rotation_angleX -= 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, COLOR_RED);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 800;
    cout << "Playing Instructions:\n";
    cout << "1. Press A, S, D & F keys to rotate the camera and Space bar to stop camera rotation\n";
    cout << "2. Press J, K, K, ;, I and O to translate the shape along axes.\n3. Press Q to exit\n\n\n";
    cout << "Please select any option by typing a, b or c and then press Enter to view that particular shape!\n";
    cout << "a. Elongated Square Bipyramid\n";
    cout << "b. Hexagonal Bipyramid\n";
    cout << "c. Decagonal Prism\n";
    cin >> shapeChosen;

    window = initGLFW(width, height);

    initGL (window, width, height);    
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void funn(int a) {
    globalRotn = a;
}

int give() {
    return globalRotn;
}

char giveShape() {
    return shapeChosen;
}