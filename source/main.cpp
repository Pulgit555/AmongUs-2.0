#include "main.h"
#include "timer.h"
#include "world.h"
#include "character.h"
#include "mirror.h"
#include "coins.h"
#include "button.h"
#include "coin_design.h"
#include "bomb.h"
#include "light.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// Ball ball1;
World world1;
Character player;
Mirror pl_mirror;
Character imposter;
Mirror im_mirror;
Coins coin[20];
Coin_design coin_design[20];
Button button1;
Button button2;
Bomb bomb[10];
Light lite;

// std::map<char, Character> Characters;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float times;

Timer t60(1.0 / 60);
Timer t20(1.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    if(times>=0&&player.d==0&&world1.finish==0)
    {
        world1.draw(VP);
        player.draw(VP);
        pl_mirror.draw(VP);
        if(world1.button2 == 1)
        {
            for(int i=0;i<12;i++)
            {
                if(coin[i].status==0)
                {
                    coin[i].draw(VP);
                    coin_design[i].draw(VP);
                }
            }
            for(int i=0;i<6;i++)
            {
                if(bomb[i].status==0)
                {
                    bomb[i].draw(VP);
                    // coin_design[i].draw(VP);
                }
            }
        }
        else{
            button2.draw(VP);
        }
        if(world1.button1 == 0)
        {
            button1.draw(VP);
            imposter.draw(VP);
            im_mirror.draw(VP);
        }
        if(world1.light==1)
        {
            lite.draw(VP);
        }
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int up    = glfwGetKey(window, GLFW_KEY_UP);
	int down    = glfwGetKey(window, GLFW_KEY_DOWN);
    int light = glfwGetKey(window, GLFW_KEY_L);
    if (left) 
    {
        int k = world1.detect_collision_l(player,pl_mirror,imposter,im_mirror);
        // cout<<k<<endl;
        if (k==0)
        {
            player.set_position(player.position.x - 0.05, player.position.y);
            pl_mirror.set_position(pl_mirror.position.x - 0.05, pl_mirror.position.y);
        }
        else if(k==2)
        {
            player.set_value(1);
            // cout<<player.d<<endl;
        }
    }
    else if (right) 
    {
        int k = world1.detect_collision_r(player,pl_mirror,imposter,im_mirror);
        if (k==0)
        {
            player.set_position(player.position.x + 0.05, player.position.y);
            pl_mirror.set_position(pl_mirror.position.x + 0.05, pl_mirror.position.y);
        }
        else if(k==2)
        {
            player.set_value(1);
            // cout<<player.d<<endl;
        }
    }
    else if (down) 
    {
        int k = world1.detect_collision_d(player,pl_mirror,imposter,im_mirror);
        if (k==0)
        {
            player.set_position(player.position.x, player.position.y - 0.05);
            pl_mirror.set_position(pl_mirror.position.x, pl_mirror.position.y - 0.05);
        }
        else if(k==2)
        {
            player.set_value(1);
            // cout<<player.d<<endl;
        }
    }
    else if (up)
    {
        int k = world1.detect_collision_u(player,pl_mirror,imposter,im_mirror);
        if (k==0)
        {
            player.set_position(player.position.x, player.position.y + 0.05);
            pl_mirror.set_position(pl_mirror.position.x, pl_mirror.position.y + 0.05);
        }
        else if(k==2)
        {
            player.set_value(1);
            // cout<<player.d<<endl;
        }
    }
    else if(light)
    {
        if(world1.light == 0)
            world1.light =1;
        else
            world1.light =0;
    }
    if(world1.button2==0)
    {
        if(button2.collision(pl_mirror)==1)
        {
            world1.button2 = 1;
        }
    }
    if(world1.button1==0)
    {
        if(button1.collision(pl_mirror)==1)
        {
            world1.button1 = 1;
            world1.task = world1.task -1;
        }
    }
    if(world1.button2 == 1)
    {
        for(int i=0;i<12;i++)
        {
            if(coin[i].status==0)
            {
                if(coin[i].collision(player,pl_mirror)==1)
                {
                    player.change_hel(2);
                    player.powerup = player.powerup+1;
                }
            }
        }
        for(int i=0;i<6;i++)
        {
            if(bomb[i].status==0)
            {
                if(bomb[i].collision(player,pl_mirror)==1)
                {
                    player.change_hel(-3);
                }
            }
        }
    }
    if(player.powerup==6&&world1.power==0)
    {
        world1.power=1;
        world1.task-=1;
    }
    if(world1.task==0)
    {
        world1.a[0][7]=0;
        if(right)
        {
            if(world1.exit_collision(player,pl_mirror)==1)
            {
                player.set_position(player.position.x + 0.1, player.position.y);
                world1.finish = 1;
            }
        }
    }
    lite.set_position(player.position.x, player.position.y);
    // int k = world1.enemy_collision(player, imposter);
    // if(k==2)
    // {
    //     player.set_value(1);
    // }
}

void tick_elements() {
    // ball1.tick();
    // world1.tick();
    // player.tick();
    // pl_mirror.tick();
    // imposter.tick();
    // im_mirror.tick();//1->up,2->down,3->left,4->right.
    if(world1.button1 == 0) 
    {
        int l =world1.movement(player ,imposter);
        int k = world1.enemy_collision(player, imposter);
        if(k==2)
        {
            player.set_value(1);
        }
        // cout<<l<<endl;
        if(l==1)
        {
            imposter.set_position(imposter.position.x ,imposter.position.y+1.0);
            im_mirror.set_position(im_mirror.position.x ,im_mirror.position.y+1.0);  
        }
        else if(l==2)
        {
            imposter.set_position(imposter.position.x ,imposter.position.y-1.0);
            im_mirror.set_position(im_mirror.position.x ,im_mirror.position.y-1.0);
        }
        else if(l==3)
        {
            imposter.set_position(imposter.position.x-1.0 ,imposter.position.y);
            im_mirror.set_position(im_mirror.position.x-1.0 ,im_mirror.position.y);
        }
        else
        {
            imposter.set_position(imposter.position.x+1.0 ,imposter.position.y);
            im_mirror.set_position(im_mirror.position.x+1.0 ,im_mirror.position.y);
        }
    }
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ball1       = Ball(0, 0, COLOR_RED);
    world1 = World(0, 0, COLOR_RED);
    player = Character(-3.5, -3, COLOR_GREEN);
    pl_mirror = Mirror(-3.4, -3, COLOR_BLUE);
    imposter = Character(3.5, -3.5, COLOR_RED);
    im_mirror = Mirror(3.4, -3.5, COLOR_BLUE);
    button2 = Button(-1,3.5, COLOR_YELLOW);
    button1 = Button(2, 3.5, COLOR_RED);
    lite = Light(0,0, COLOR_B);
    for(int i=0;i<6;i++)
    {
        coin[i]= Coins(-2.5+i,-2, COLOR_BROWN);
        coin_design[i] = Coin_design(-2.5+i,-2, COLOR_BLACK);
    }
    for(int i=0;i<6;i++)
    {
        coin[i+6]= Coins(-2.5+i,2, COLOR_BROWN);
        coin_design[i+6] = Coin_design(-2.5+i,2, COLOR_BLACK);
    }
    for(int i=0;i<6;i++)
    {
        bomb[i] = Bomb(-2.5+i,0, COLOR_BLACK);
        // coin_design[i+6] = Coin_design(-2.5+i,2, COLOR_BLACK);
    }
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
    int width  = 600;
    int height = 600;
    // glutInit( & argc, argv );

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}
    // // Lighting 
    // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// glEnable(GL_COLOR_MATERIAL);
	// glEnable(GL_LIGHTING);
	// glEnable(GL_DEPTH_TEST);
    int viewportWidth, viewportHeight;
    GLTtext *text1 = gltCreateText();
    GLTtext *text3 = gltCreateText();
    int aa=1;
    char bb[100],cc[100],dd[100],ee[100],ff[100],gg[100];
	GLTtext *text2 = gltCreateText();
    GLTtext *text4 = gltCreateText();
    GLTtext *text5 = gltCreateText();
    GLTtext *text6 = gltCreateText();
    sprintf(gg, "EXIT");
    gltSetText(text6,gg);
    times = 50;
    float light_times =0;
    float cur_time = glfwGetTime();
    float in_ti = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
        glViewport(0, 0, viewportWidth, viewportHeight);
        // Process timers
        if(player.d==1)
        {
            sprintf(ff, "YOU LOST!!");
            gltSetText(text5,ff);
            draw();
            gltBeginDraw();

            gltColor(0.5f, 0.5f, 0.5f, 0.0f);
            gltDrawText2DAligned(text5,
                (GLfloat)(viewportWidth/2),
                (GLfloat)(viewportHeight/2),
                6.0f,
                GLT_CENTER, GLT_CENTER);
            gltEndDraw();
        }
        else if(world1.finish==1)
        {
            sprintf(ff, "YOU WON!!");
            gltSetText(text5,ff);
            sprintf(bb, "Health: %d",player.health);
            gltSetText(text1,bb);
            draw();
            gltBeginDraw();

            gltColor(0.0f, 1.0f, 0.0f, 0.0f);
            gltDrawText2DAligned(text5,
                (GLfloat)(viewportWidth/2),
                (GLfloat)(viewportHeight/2),
                6.0f,
                GLT_CENTER, GLT_CENTER);
            gltDrawText2DAligned(text1,
                (GLfloat)(viewportWidth/2),
                (GLfloat)(viewportHeight/2+100),
                1.0f,
                GLT_CENTER, GLT_CENTER);
            gltEndDraw();
        }
        else 
        {
            if (t60.processTick()) {
                // 60 fps
                // OpenGL Draw commands
                float fi = glfwGetTime();
                if(light_times>2)
                {
                    player.health += 1;
                    light_times -=2;
                }
                if(world1.light==1)
                {
                    light_times +=  fi-cur_time;
                    cur_time=fi;
                }
                else{
                    player.health += light_times/2;
                    light_times=0;
                    cur_time=fi;
                }
                if(times>=0)
                    times = times -fi+in_ti;
                in_ti = fi;
                if(times < 0)
                {
                    sprintf(ff, "GAME OVER!!");
                    gltSetText(text5,ff);
                    draw();
                    gltBeginDraw();

                    gltColor(1.0f, 1.0f, 1.0f, 0.0f);
                    gltDrawText2DAligned(text5,
                        (GLfloat)(viewportWidth/2),
                        (GLfloat)(viewportHeight/2),
                        6.0f,
                        GLT_CENTER, GLT_CENTER);
                    gltEndDraw();
                    // break;
                }
                else 
                {
                    // GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
                    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
                    // glEnable(GL_LIGHT0);


                    // // Set lighting intensity and color
                    // GLfloat qaAmbientLight[]	= {0.2, 0.2, 0.2, 1.0};
                    // GLfloat qaDiffuseLight[]	= {1.0, 1.0, 1.0, 1.0};
                    // GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
                    // glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
                    // glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
                    // glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
                    // glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
                    // // Set the light position
                    // GLfloat qaLightPosition[]	= {1.0, 1.0, 0.0, 0.0};
                    // glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
                    
                    sprintf(bb, "Health: %d",player.health);
                    gltSetText(text1,bb);
                    sprintf(dd,"Tasks: %d",world1.task);
                    gltSetText(text2,dd);
                    if(world1.light == 0)
                    {
                        sprintf(cc,"Light: On");
                    }
                    else{
                        sprintf(cc,"Light: Off");
                    }
                    gltSetText(text3,cc);
                    sprintf(ee,"Time: %d",(int)times);
                    gltSetText(text4,ee);
                    draw();
                    gltBeginDraw();

                    gltColor(0.0f, 1.0f, 1.0f, 1.0f);
                    // gltDrawText2D(text1, 0.0f, 0.0f, 1.0f); // x=0.0, y=0.0, scale=1.0
                    // gltDrawText2D(text3, 1.0f, 1.0f, 1.0f);
                    gltDrawText2DAligned(text1,
                        (GLfloat)(0),
                        (GLfloat)(0),
                        1.0f,
                        GLT_LEFT, GLT_TOP);
                    gltDrawText2DAligned(text2,
                        (GLfloat)(0),
                        (GLfloat)(15),
                        1.0f,
                        GLT_LEFT, GLT_TOP);
                    gltDrawText2DAligned(text3,
                        (GLfloat)(0),
                        (GLfloat)(30),
                        1.0f,
                        GLT_LEFT, GLT_TOP);
                    gltDrawText2DAligned(text4,
                        (GLfloat)(0),
                        (GLfloat)(45),
                        1.0f,
                        GLT_LEFT, GLT_TOP);
                    gltDrawText2DAligned(text6,
                        (GLfloat)(viewportWidth),
                        (GLfloat)(0),
                        1.0f,
                        GLT_RIGHT, GLT_TOP);
                    gltEndDraw();
                }
                if (t20.processTick()) {
                    tick_elements();
                }
            }
            // break;
        }
        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);
        if(times>=0&&player.d==0&&world1.finish==0)
        {
            tick_input(window);
        }
            // break;

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    gltDeleteText(text1);
	gltDeleteText(text2);
    gltDeleteText(text3);
	gltDeleteText(text4);
    gltDeleteText(text5);
	gltDeleteText(text6);
    gltTerminate();
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

// void RenderString(float x, float y, void *font, const unsigned char* string)
// {  
//   char *c;

//   glColor3f(1., 1., 1.); 
//   glRasterPos2f(x, y);
// //   const unsigned char* st = string;
//   glutBitmapString(font, string);
// }
