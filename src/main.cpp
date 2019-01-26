#include "main.h"
#include "ball.h"
#include "world.h"
#include "coin.h"
#include "gem.h"
#include "beams.h"
#include "magnet.h"
#include "lines.h"
#include "flying1.h"
#include "flying2.h"
#include "boomerang.h"
#include "balloon.h"
#include "display.h"
#include "dragon.h"
#include "semicircle.h"
// #include "iceball.h"

#include <unistd.h>
// #include <>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

int no_balloon = 0;
int final_score;
float no_semicircle;
int move_semicircle;
/**************************
* Customizable functions *
**************************/

Ball ball1;
World world1[1000];
World world2[1000];
Coin coin[1000];
Gem gem[1000];
Magnet magnet[1000];
Beams beam;
Lines line[1000];
Flying1 flying1[100];
Flying2 flying2;
Boomerang boomerang[100];
Balloon balloon[1000];
Display display1;
Display display2;
Display display3;
Display display4;

Display health_display1;
Display health_display2;
Display health_display3;
Display health_display4;
Display health_display5;


Dragon dragon;
Semicircle semicircle[1000];
// Iceball iceball[1000];


float screen_zoom = 0.1, screen_center_x = 39.5, screen_center_y = 30;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

// Eye - Location of camera. Don't change unless you are sure!!
// glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
glm::vec3 eye ( 0, 0, 1);

// Target - Where is the camera looking at.  Don't change unless you are sure!!
glm::vec3 target (0, 0, 0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

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
    beam.draw(VP);
    flying2.draw(VP);
    display1.draw(VP);
    display2.draw(VP);
    display3.draw(VP);
    display4.draw(VP);

    health_display1.draw(VP);
    health_display2.draw(VP);
    health_display3.draw(VP);
    health_display4.draw(VP);
    health_display5.draw(VP);
    dragon.draw(VP);
    // semicircle.draw(VP);

    // boomerang.draw(VP);
    // flying1.draw(VP);
    for (int i = 0; i < 1000; ++i)
    {
        world1[i].draw(VP);
        world2[i].draw(VP);
    }
    for (int i = 0; i < 400; ++i)
    {
        coin[i].draw(VP);
    }
    for (int i = 0; i < 200; ++i)
    {
        gem[i].draw(VP);
    }
    for (int i = 0; i < 10; ++i)
    {
        line[i].draw(VP);
    }
    for (int i = 0; i < 10; ++i)
    {
        magnet[i].draw(VP);
    }
    for (int i = 0; i < 10; ++i)
    {
        flying1[i].draw(VP);
    }
    for (int i = 0; i < 10; ++i)
    {
        boomerang[i].draw(VP);
    }
    for (int i = 0; i < 1000; ++i)
    {
        balloon[i].draw(VP);
    }
    for (int i = 0; i < 1000; ++i)
    {
        semicircle[i].draw(VP);
    }
    // for (int i = 0; i < 1000; ++i)
    // {
    //     iceball[i].draw(VP);
    // }
    display1.number = final_score%10;
    display2.number = (final_score/10)%10;
    display3.number = (final_score/100)%10;
    display4.number = (final_score/1000)%10;

    health_display1.number = ball1.health%10;
    health_display2.number = (ball1.health/10)%10;
    health_display3.number = (ball1.health/100)%10;
    health_display4.number = (ball1.health/1000)%10;
    health_display5.number = (ball1.health/10000)%10;
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int shoot = glfwGetKey(window, GLFW_KEY_S);
    if (left)
        ball1.move_left();
    else if (right)
        ball1.move_right();
    else if (space && ball1.position.y < 57)
        ball1.jump();
    else if (shoot)
    {
        balloon[no_balloon++] = Balloon(ball1.position.x , ball1.position.y, COLOR_NAVY);
    }

    glfwSetScrollCallback(window, scroll_callback);
}

void tick_elements() {
    // boomerang.tick();
    flying2.tick();
    ball1.tick();
    for (int i = 0; i < 400; ++i)
    {
        coin[i].tick();
    }
    for (int i = 0; i < 200; ++i)
    {
        gem[i].tick();
    }
    for (int i = 0; i < 10; ++i)
    {
        flying1[i].tick();
    }
    for (int i = 0; i < 10; ++i)
    {
        if(boomerang[i].position.x - ball1.position.x < 30)
            boomerang[i].tick();
    }
    for (int i = 0; i < 1000; ++i)
    {
        balloon[i].tick();
    }
    // for (int i = 0; i < 1000; ++i)
    // {
    //     iceball[i].tick();
    // }
    camera_rotation_angle += 1;
    
    // printf("Ball Position-%f Eye Position-%f\n", ball1.position.x, eye.x);
    if(ball1.position.x > eye.x)
    {
        eye.x += 0.05;
        target.x += 0.05;
        beam.tick();

        display1.tick();
        display2.tick();
        display3.tick();
        display4.tick();

        health_display1.tick();
        health_display2.tick();
        health_display3.tick();
        health_display4.tick();
        health_display5.tick();

    dragon.tick();

    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1       = Ball(0, 0, COLOR_RED);
    // semicircle  = Semicircle(40, 40, COLOR_PINK);
    beam        = Beams(0, 20, COLOR_GOLD);

    flying2     = Flying2(999, 0, COLOR_PINK);

    // boomerang[0]   = Boomerang(70, 45, COLOR_PINK);

    display1    =Display(70, 58, COLOR_MAROON);
    display2    =Display(67, 58, COLOR_MAROON);
    display3    =Display(64, 58, COLOR_MAROON);
    display4    =Display(61, 58, COLOR_MAROON);

    health_display1    =Display(15, 58, COLOR_MAROON);
    health_display2    =Display(12, 58, COLOR_MAROON);
    health_display3    =Display(9, 58, COLOR_MAROON);
    health_display4    =Display(6, 58, COLOR_MAROON);
    health_display5    =Display(3, 58, COLOR_MAROON);

    dragon      = Dragon(65, 20, COLOR_DRAGON);
    int r = 0;
    for (int i = 70; i < 1000; i+=200)
    {
        boomerang[r++] = Boomerang(i, 45, COLOR_PINK);
    }
    for (int i = 0; i < 1000; ++i)
    {
        world1[i]       = World(i, -5.5, COLOR_GREEN);
        world2[i]       = World(i, 65, COLOR_GREEN);

    }

    int j = 0, n1, n2;

    for (int c = 1; c <= 100; c++) 
    {
        n1 = rand() % 1000 + 1;
        n2 = rand() % 60 + 1;
        coin[j++] = Coin(n1, n2, COLOR_GOLD);
        coin[j++] = Coin(n1+2, n2, COLOR_GOLD);
        coin[j++] = Coin(n1+4, n2, COLOR_GOLD);
        coin[j++] = Coin(n1+6, n2, COLOR_GOLD);
    }

    int k = 0, n3;

    for (int i = 0; i < 50; ++i)
    {
        n3 = rand() % 1000 + 1;
        gem[k++] = Gem(n3, 63, COLOR_MAROON);
        gem[k++] = Gem(n3+2, 63, COLOR_MAROON);
        gem[k++] = Gem(n3+4, 63, COLOR_MAROON);
        gem[k++] = Gem(n3+6, 63, COLOR_MAROON);
    }

    int n4, l=0;

    for (int i = 0; i < 1000; i+=100)
    {
        n4 = rand() % 180 + 1;
        line[l++]           = Lines(i, 30, COLOR_GOLD, n4);
    }
    int m = 0;
    for (int i = 50; i < 1000; i+=100)
    {
        magnet[m++] = Magnet(i, 20, COLOR_GOLD);
    }
    int n=0;
    for (int i = 400; i < 1000; i+=500)
    {
        flying1[n++]     = Flying1(i, 0, COLOR_SEA);

    }
    int p = 0;
    for (int i = 50; i < 1000; i+=200)
    {
        semicircle[p++] = Semicircle(i, 40, COLOR_MAROON);
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
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
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            reset_screen();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            // usleep(0.1);

            tick_elements();
            tick_input(window);
            for (int i = 0; i < 400; ++i)
            {
                if (detect_collision(ball1.ball_bbox, coin[i].coin_bbox) && coin[i].flag == 1)
                {
                    coin[i].flag = 0;
                    final_score += coin[i].score;
                }
            }
            for (int i = 0; i < 200; ++i)
            {
                if (detect_collision(ball1.ball_bbox, gem[i].gem_bbox) && gem[i].flag == 1)
                {
                    gem[i].flag = 0;
                    final_score += gem[i].score;
                }
            }
            for (int i = 0; i < 10; ++i)
            {
                if (detect_collision(ball1.ball_bbox, magnet[i].magnet_bbox) && magnet[i].flag == 1)
                {
                    ball1.magnet = 1;
                }
            }
            for (int i = 0; i < 10; ++i)
            {
                if (detect_collision(ball1.ball_bbox, flying1[i].flying1_bbox) && flying1[i].flag == 1)
                {
                    ball1.flag_flying1 = 1;
                    flying1[i].flag = 0;
                    final_score = final_score * 2;
                }
            }
            if (detect_collision(ball1.ball_bbox, flying2.flying2_bbox) && flying2.flag == 1)
            {
                flying2.flag = 0;
                ball1.health += 10000;
            }
            for (int i = 0; i < 1000; ++i)
            {
                for (int j = 0; j < 10; ++j)
                {
                    if (detect_collision(balloon[i].balloon_bbox, line[j].lines_bbox) && balloon[i].flag == 1)
                    {
                        balloon[i].flag = 0;
                        line[j].flag = 0;
                    }
                }
            }
            for (int i = 0; i < 10; ++i)
            {
                if (detect_collision(ball1.ball_bbox, line[i].lines_bbox) && line[i].flag == 1)
                {
                        ball1.lives -= 1;
                }
            }
            for (int i = 0; i < 1000; ++i)
            {
                if (detect_collision(balloon[i].balloon_bbox, dragon.dragon_bbox) && dragon.flag == 1)
                    dragon.health --;
            }
            for (int i = 0; i < 100; ++i)
              {
                  if (detect_collision(ball1.ball_bbox, boomerang[i].boomerang_bbox))
                  {
                    ball1.health -= 10;
                  }
              }  
            if (detect_collision(ball1.ball_bbox, beam.beams_bbox) && beam.flag == 1)
            {
                printf("beam collide\n");
                ball1.health --;
            }
            for (int i = 0; i < 100; i++)
            {
                if (detect_collision(ball1.ball_bbox, semicircle[i].semicircle_bbox))
                {
                    move_semicircle = 1;
                    no_semicircle = semicircle[i].position.x;
                }
            }

            if(move_semicircle == 1)
            {
                printf("Move semicircle\n");
                // printf("%f %f\n", ball1.position.x, ball1.position.y);
                printf("%f\n", no_semicircle);
                ball1.health+=10;
                ball1.position.y = 40 + sqrt(121 - pow((ball1.position.x - no_semicircle),2));
                ball1.position.x += 0.5;
                // printf("%f %f\n", ball1.position.x, ball1.position.y);

            }
            move_semicircle = 0;

            if(ball1.lives == 0 || ball1.health == 0 || ball1.position.x == 900)
                quit(window);

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        // printf("%d\n",final_score );

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
