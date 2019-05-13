#include "main.h"
#include "timer.h"
#include "ball.h"
#include "floor.h"
#include "checkpoints.h"
#include "bombs.h"
#include "missile.h"
#include "check.h"
#include "arrow.h"
#include "smokering.h"
#include "canon.h"
#include "fuel.h"
#include "health.h"
#include "fuelup.h"
#include "parachutes.h"
#include "speedometer.h"
#include "altitude.h"
#include "volcano.h"
using namespace std; 

GLMatrices Matrices,Matrices1;
GLuint     programID;
GLFWwindow *window;
float score=0;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Floor floor1;
vector<Checkpoint> checkpoint;
vector<Bombs>  bomb;
vector<Missile> missile;
vector<Check> chec;
vector<Smokering> smoke;
vector<Canon> enemy1;
vector<Fuelup> fuelup;
vector<Parachutes> parachutes;
vector<Volcano> volcano1;
Speedometer speedo;
Cameraview_t view;
Arrow arr;
Fuel fuel;
Health health;
Altitude altitude1;
float fuel_left=100;
float health_left=100;
float speed=0;
float height_a=0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 520);

/* Render the scene with openGL */
    glm::vec3 eye,target,up,eye1,target1,up1;
void heli_camera(float x,float y)
{
    if(view==HELICOPTER)
    {
        target.x=ball1.position.x + x-400;
        if(y-400<=0){
            target.y=ball1.position.y+(400-y)/2;
        }
    }
    else
    {
        return;
    }
}
void zoom_camera(int type)
{
    if(view==HELICOPTER)
    {
        float n=target.z-eye.z;
        if(type==1)
        {
            if(eye.z-target.z>10)
                eye.z-=5;
        }
        else if(type==-1)
        {
            if(eye.z-target.z<200)
            {   
                eye.z+=5;
            }
        }
        eye.z=(target.x-eye.x)*(eye.z-target.z)/n+target.x;
        eye.y=(target.y-eye.y)*(eye.z-target.z)/n+target.y;

    }
}
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    if(view==FOLLOW)
    {
        eye=glm::vec3 (ball1.position.x+3*ball1.lo_z.x+2*ball1.lo_y.x,ball1.position.y+3*ball1.lo_z.y+2*ball1.lo_y.y,ball1.position.z+3*ball1.lo_z.z+2*ball1.lo_y.z);
        target=glm::vec3 (ball1.position.x, ball1.position.y,ball1.position.z);
        up=glm::vec3 (0, 1, 0);
    }
    if(view==TOP)
    {
        eye=glm::vec3 (ball1.position.x,ball1.position.y+20,ball1.position.z);
        target=glm::vec3 (ball1.position.x, ball1.position.y,ball1.position.z);
        up=glm::vec3 (0, 0, -1);

    }
    if(view==PLANE)
    {
        eye=glm::vec3 (ball1.position.x-2*ball1.lo_z.x,ball1.position.y-2*ball1.lo_z.y,ball1.position.z-2*ball1.lo_z.z);
        target=glm::vec3 (ball1.position.x-3*ball1.lo_z.x, ball1.position.y-3*ball1.lo_z.y,ball1.position.z-3*ball1.lo_z.z);
        up=glm::vec3 (0, 1, 0);
        
    }
    if(view==TOWER)
    {
        eye=glm::vec3 (10,30,10);
        target=glm::vec3 (0, 0,0);
        up=glm::vec3 (0, 1, 0);
    }
    // cout<<view<<'\n';
    eye1=glm::vec3 ( 0,0,20);
        target1=glm::vec3 (0,0,0);
        up1=glm::vec3 (0, 1, 0);
        Matrices1.view = glm::lookAt( eye1, target1, up1 );
     // Rotating Camera for 3D
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
   
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP1 =Matrices1.projection * Matrices1.view ;

    glm::mat4 MVP;
    glm::mat4 MVP1;

    // Scene render
    ball1.draw(VP);
    floor1.draw(VP);
    for(int i=0;i<checkpoint.size();i++)
    {
        checkpoint[i].draw(VP);
    }
    for(int i=0;i<bomb.size();i++)
    {
        bomb[i].draw(VP);
    }
    for(int i=0;i<missile.size();i++)
    {
        missile[i].draw(VP);
    }
    for(int i=0;i<chec.size();i++)
    {
        chec[i].draw(VP);
    }
    for(int i=0;i<smoke.size();i++)
    {
        smoke[i].draw(VP);
    }
    for(int i=0;i<enemy1.size();i++)
    {
        enemy1[i].draw(VP);
    }
    for(int i=0;i<fuelup.size();i++)
    {
        fuelup[i].draw(VP);
    }
    for(int i=0;i<parachutes.size();i++)
    {
        parachutes[i].draw(VP);
    }
    for(int i=0;i<volcano1.size();i++)
    {
        volcano1[i].draw(VP);
    }
    arr.draw(VP1);
    fuel=Fuel(-3.5,0,fuel_left,COLOR_BLACK);
    health=Health(0,-3,health_left,COLOR_BLACK);
    speedo=Speedometer(0,-3+0.22,speed,COLOR_BLACK);
    fuel.draw(VP1);
    health.draw(VP1);
    speedo.draw(VP1);
    altitude1=Altitude(3.5,0,ball1.position.y,COLOR_GOLDEN );
    altitude1.draw(VP1);
}

int x;
int flag;
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up= glfwGetKey(window,GLFW_KEY_UP);
    int down=glfwGetKey(window,GLFW_KEY_DOWN);
    int w=glfwGetKey(window,GLFW_KEY_W);
    int s=glfwGetKey(window,GLFW_KEY_S);
    int e=glfwGetKey(window,GLFW_KEY_E);
    int r=glfwGetKey(window,GLFW_KEY_R);
    int b=glfwGetKey(window,GLFW_KEY_B);
    int m=glfwGetKey(window,GLFW_KEY_M);
    if(m)
    {
        Missile mis1;
        mis1=Missile(ball1.position.x,ball1.position.y-1,ball1.position.z,COLOR_MISSILE);
        missile.push_back(mis1);
    }
    if(b!=flag && flag==1)
    {
        Bombs bomb1;
        bomb1= Bombs(ball1.position.x,ball1.position.y-1,ball1.position.z,COLOR_BLACK);
        bomb.push_back(bomb1);
        flag=0;
    }
    flag=b;
    if(w)
    {

        if(ball1.rotationx<45)
            ball1.rotationx+=0.5;
        ball1.position.x+=0.6*ball1.lo_y.x;
        if(ball1.position.y<100)
            ball1.position.y+=0.6*ball1.lo_y.y;
        ball1.position.z+=0.6*ball1.lo_y.z;
    } 
   
    if(s)
    {
        if(ball1.rotationx>-20)
        {
            ball1.rotationx-=0.5;
        }
        ball1.position.x-=0.6*ball1.lo_y.x;
        if(ball1.position.y>-9)
            ball1.position.y-=0.6*ball1.lo_y.y;
        else
            exit(0);
        ball1.position.z-=0.6*ball1.lo_y.z;
    }
    if(e)
    {
        if(ball1.rotationz<30)
            ball1.rotationz+=0.5;
    }
    if(r)
    {
        if(ball1.rotationz>-30)
            ball1.rotationz-=0.5;
    }
    if(left)
    {
        ball1.rotationy+=0.5;
    }
    if(right)
    {
        ball1.rotationy-=0.5;
    }
    if(up)
    {

        if(speed<100)
            speed+=2;
        ball1.position.x-=0.5*ball1.lo_z.x;
            ball1.position.y-=0.5*ball1.lo_z.y;
        ball1.position.z-=0.5*ball1.lo_z.z;
        if(fuel_left>0)
            fuel_left-=0.05;
    }
    else
    {
        if(speed>=0)
        {
            speed-=1;
        }
    }    
    if(down)
    {
        ball1.position.x+=0.5*ball1.lo_z.x;
        ball1.position.y+=0.5*ball1.lo_z.y;
        ball1.position.z+=0.5*ball1.lo_z.z;
    }
}
void bomb_gravity()
{
    for(int i=0;i<bomb.size();i++)
    {
        bomb[i].position.y-=0.1;
    }
}
void bombs_elements()
{
    bomb_gravity() ;
}
void missile_elements()
{
    for(int i=0;i<missile.size();i++)
    {
        missile[i].position.x-=0.5*ball1.lo_z.x+0.1*ball1.lo_y.x;
        missile[i].position.y-=0.5*ball1.lo_z.y+0.1*ball1.lo_y.y;
        missile[i].position.z-=0.5*ball1.lo_z.z+0.1*ball1.lo_y.z;
        
    }
    
}
void check_elements()
{
        bounding_box_t a,b;
        a.height=6;
        a.length=10;
        a.width=10;
        a.x=chec[0].position.x;
        a.y=chec[0].position.y+3;
        a.z=chec[0].position.z;
        for(int i=0;i<bomb.size();i++)
        {
            b.height=1;
            b.length=1;
            b.width=1;
            b.x=bomb[i].position.x;
            b.y=bomb[i].position.y;
            b.z=bomb[i].position.z;
            if(detect_collision(a,b))
            {
                score+=10;
                cout<<"collision bomb with checkpoint"<<'\n';
                chec.erase(chec.begin()+0);
                enemy1.clear();
                bomb.clear();
            }
        }
        for(int i=0;i<missile.size();i++)
        {
            b.height=1;
            b.length=1;
            b.width=1;
            b.x=missile[i].position.x;
            b.y=missile[i].position.y;
            b.z=missile[i].position.z;
            if(detect_collision(a,b))
            {
                score+=10;
                cout<<"collision missile"<<'\n';
                chec.erase(chec.begin()+0);
                enemy1.clear();
                missile.clear();
            }
        }
}
void arrow_elements()
{
    float a=chec[0].position.x-ball1.position.x;
    float b=chec[0].position.z-ball1.position.z;
    float z=sqrt(a*a+b*b);
    a/=z;
    b/=z;
    float theta=acos(a*ball1.lo_x.x+b*ball1.lo_x.z)*180/M_PI;
    arr.rotation=theta-90;
}
float t=0;
void enemy1_elements()
{
    if(clock()-t>5000000)
    {
        Canon c;
        c= Canon(chec[0].position.x,chec[0].position.y+6,chec[0].position.z,COLOR_BLACK);
        enemy1.push_back(c);
        t=clock();
    }
    float a=ball1.position.x-chec[0].position.x;
    float b=ball1.position.y-chec[0].position.y-6;
    float c=ball1.position.z-chec[0].position.z;
    float z=sqrt(a*a+b*b+c*c);
    a/=z;
    b/=z;
    c/=z;
    for(int i=0;i<enemy1.size();i++)
    {  
        enemy1[i].position.x+=a;
        enemy1[i].position.y+=b;
        enemy1[i].position.z+=c;
    }
    bounding_box_t x1,x2;
    x1.height=1;
    x1.length=4;
    x1.width=1;
    x1.x=ball1.position.x;
    x1.y=ball1.position.y;
    x1.z=ball1.position.z;
    for(int i=0;i<enemy1.size();i++)
    {
        x2.height=1;
        x2.length=1;
        x2.width=1;
        x2.x=enemy1[i].position.x;
        x2.y=enemy1[i].position.y;
        x2.z=enemy1[i].position.z;
        if(detect_collision(x1,x2))
        {
            cout<<"collision with plane"<<'\n';
            health_left-=5;
            enemy1.erase(enemy1.begin()+i);
        }
    }

}
void fuelup_elements()
{
    bounding_box_t x1,x2;
    x1.height=1;
    x1.length=4;
    x1.width=1;
    x1.x=ball1.position.x;
    x1.y=ball1.position.y;
    x1.z=ball1.position.z;
    for(int i=0;i<fuelup.size();i++)
    {
        x2.height=2;
        x2.length=2;
        x2.width=2;
        x2.x=fuelup[i].position.x;
        x2.y=fuelup[i].position.y;
        x2.z=fuelup[i].position.z;
        if(detect_collision(x1,x2))
        {
            fuel_left+=50;
            if(fuel_left>100)
            {
                fuel_left=100;
            }
            fuelup.erase(fuelup.begin()+i);
            // cout<<"collision with plane"<<'\n';
            // health_left-=5;
            // enemy1.erase(enemy1.begin()+i);
        }
    }
}
void parachutes_elements()
{
    for(int i=0;i<parachutes.size();i++)
    {
        parachutes[i].position.y-=1;
        if(parachutes[i].position.y<-10)
        {
            parachutes[i].position.y+=3000;
        }
    }
    bounding_box_t x2,b;
    for(int i=0;i<parachutes.size();i++)
    {
        x2.height=15;
        x2.length=20;
        x2.width=20;
        x2.x=parachutes[i].position.x;
        x2.y=parachutes[i].position.y+7.5;
        x2.z=parachutes[i].position.z;
        for(int j=0;j<missile.size();j++)
        {
            b.height=1;
            b.length=1;
            b.width=1;
            b.x=missile[j].position.x;
            b.y=missile[j].position.y;
            b.z=missile[j].position.z;
            if(detect_collision(x2,b))
            {
                missile.erase(missile.begin()+j);
                parachutes.erase(parachutes.begin()+i);
                cout<<"parachutes collide"<<'\n';
            }
        }
        
    }
    
}
void volcano_elements()
{
    for(int i=0;i<volcano1.size();i++)
    {
        if(abs(volcano1[i].position.x-ball1.position.x)<12 && abs(volcano1[i].position.z-ball1.position.z)<12)
        {
            exit(0);
        }
    }
}
void tick_elements() {
    if(ball1.position.y<-9 || fuel_left<=0)
        exit(0);
    ball1.tick();
    floor1.tick();
    for(int i=0;i<checkpoint.size();i++)
        checkpoint[i].tick();
    bombs_elements();
    missile_elements();
    check_elements();
    arrow_elements();
    enemy1_elements();
    fuelup_elements();
    parachutes_elements();
    volcano_elements();
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1       = Ball(0, 10, COLOR_VOILET);
    floor1       = Floor(0,0,COLOR_BLUE);
    Checkpoint a;
    Parachutes p;
    double x=15,x1=30;
    float theta =57,theta1=23;;
    for(int i=0;i<100;i++)
    {
        p=Parachutes(x1*cos(theta1*M_PI/180.0),rand()%1000+100,x1*sin(theta1*M_PI/180.0),COLOR_YELLOW);
        a=Checkpoint(x*cos(theta*M_PI/180.0),-10,x*sin(theta*M_PI/180.0),COLOR_GREEN);
        checkpoint.push_back(a);     
        parachutes.push_back(p);
        theta+=57;
        theta1+=29;
        x+=15;
        x1+=23;
    }
    x=50;
    Fuelup f;
    theta1=0;
    Check c;
    Volcano v;
    float x2=107,theta2=123;
    for(int i=0;i<100;i++)
    {
        f=Fuelup(x*cos(theta1*M_PI/180.0),10,x*sin(theta*M_PI/180.0),COLOR_FUELUP);
        fuelup.push_back(f);
        c=Check(x*cos(theta*M_PI/180.0),-10,x*sin(theta*M_PI/180.0),COLOR_BLACK);
        chec.push_back(c);
        v=Volcano(x2*cos(theta2*M_PI/180.0),-10,x2*sin(theta2*M_PI/180.0),COLOR_BLACK);
        volcano1.push_back(v);
        theta+=27;
        theta1+=155;
        theta2+=39;
        x2+=200;
        x+=50;
    }
    Smokering s;
    theta=37;
    x=13;
    for(int i=0;i<100;i++)
    {
        s=Smokering(x*cos(theta*M_PI/180.0),5,x*sin(theta*M_PI/180.0),COLOR_GREY);
        smoke.push_back(s);
        x+=30;
        theta+=102;
    }
    arr= Arrow(0,3,0,COLOR_DARKRED);
    fuel=Fuel(-3.5,0,0,COLOR_BLACK);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices1.MatrixID = glGetUniformLocation(programID, "MVP1");



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
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            char x[1000];
            sprintf(x,"SCORE : %d  Health : %d Fuel : %d" ,(int)score,(int)health_left,(int)fuel_left);
            glfwSetWindowTitle(window,x);
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
           (abs(a.y - b.y) * 2 < (a.height + b.height)) && ((abs(a.z-b.z)*2 <(a.length +b.length)));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(135*M_PI/180, (double)1, 0.1,(double)10000);
    Matrices1.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);


}
