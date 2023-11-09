// Tutorial activity: walking man
/////////////////////////////////

#include <iostream>
#include <cmath>
#include <glew.h>
#include <freeglut.h>

static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static int animate = 0;
static float angle = 0.0;
static int animate_time = 100;
static int forward = 0;

static float leftArmAngle = 0.0;
static float rightArmAngle = 0.0;

float x_ball = 0.0f;        // Initial X position of the ball
float y_ball= 0.0f;        // Initial Y position of the ball
float initialVelocity = 0.0f; // Initial velocity
float launchAngle = 45.0f; // Launch angle in degrees
const float gravity = 9.81f; // Acceleration due to gravity

// Time step and timer interval
float deltaTime = 0.01f;  // Time step
int timerInterval = 10;   // Timer interval (milliseconds)
bool Donot_return = false;
int animation_ball = 1;
int counter =0;
bool move = false;
// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();

    // Draw the wall (rectangle) on the right side of the window.
    glPushMatrix();
// Modeling transformations.
    glTranslatef(25.0, 0.0, -20.0); // Adjust the Z-coordinate to center the wall.
// Apply a 90-degree rotation around the Y-axis
    glRotatef(90.0, 0.0, 1.0, 0.0);

// Define the wall dimensions based on the window's height and depth.
    float wallHeight = 100.0; // Should match the window's height.
    float wallDepth = 10.0; // Adjust this as needed.

    glBegin(GL_QUADS);
    glVertex3f(wallDepth / 2, -wallHeight / 2, -wallDepth / 2);
    glVertex3f(wallDepth / 2, -wallHeight / 2, wallDepth / 2);
    glVertex3f(wallDepth / 2, wallHeight / 2, wallDepth / 2);
    glVertex3f(wallDepth / 2, wallHeight / 2, -wallDepth / 2);
    glEnd();
    glPopMatrix();

    // Modeling transformations.
    glTranslatef(-10.0, 0.0, -20.0);

    // Apply a 90-degree rotation around the Y-axis
    glRotatef(90.0, 0.0, 1.0, 0.0);
//    glRotatef(Zangle, 0.0, 0.0, 1.0);
//    glRotatef(Yangle, 0.0, 1.0, 0.0);
//    glRotatef(Xangle, 1.0, 0.0, 0.0);


    //torso
    glPushMatrix();
    glScalef(1.0, 3.0, 0.5);
    glutWireCube(5.0);
    glPopMatrix();

    //head
    glPushMatrix();
    glTranslatef(0.0, 9.0, 0.0);
    glutWireSphere(2, 10, 10);
    glPopMatrix();
    // Create a ball
    glPushMatrix();
    glTranslatef(0, y_ball, x_ball);
//    glRotatef(ballAngle, 1.0, 0.0, 0.0);
    glutWireSphere(1.5, 10, 10);
    glPopMatrix();

    //left leg
    glPushMatrix();
    glTranslatef(0.0, -7.5, 0.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 7.5, 0.0);

    glTranslatef(1.0, -10.5, 0.0);
    glScalef(1.0, 4.0, 1.0);
    glutWireCube(1.5);
    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslatef(0.0, -7.5, 0.0);
    glRotatef(-angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 7.5, 0.0);

    glTranslatef(-1.0, -10.5, 0.0);
    glScalef(1.0, 4.0, 1.0);
    glutWireCube(1.5);
    glPopMatrix();

    // Draw the left arm
    glPushMatrix();
    glTranslatef(2.0, 6.0, 0.0);
    glRotatef(leftArmAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -3.0, 0.0);
    glScalef(1.0, 4.0, 1.0);
    glutWireCube(1.5);
    glPopMatrix();

    // Draw the right arm
    glPushMatrix();
    glTranslatef(-1.0, 6.0, 0.0);
    glRotatef(rightArmAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -3.0, 0.0);
    glScalef(1.0, 4.0, 1.0);
    glutWireCube(1.5);
    glPopMatrix();

    glutSwapBuffers();

}


// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void move_ball(int value){
    if(move)
    {
        x_ball -= 0.5;
        if (counter%2 ==0){
            y_ball -=0.7;


        }
        else{
            y_ball +=0.7;

        }



        counter += 1;



        std::cout<<counter;

    }



    if (counter > 8 )
    {
        counter++;

        move = false;
       if (counter < 13)
       {
           x_ball -= 0.5;
       }
    }

    glutPostRedisplay();
    glutTimerFunc(animate_time, move_ball, 1);


}
void animate_ball(int value){
    if (animation_ball)
    {

                if (x_ball < 23.756 && !Donot_return)
                {
                    float radians = launchAngle * 3.14159265 / 180.0;
                    float horizontalVelocity = initialVelocity * cos(radians);
                    float verticalVelocity = initialVelocity * sin(radians) - gravity * deltaTime;
                    x_ball += horizontalVelocity * deltaTime;
                    y_ball += verticalVelocity * deltaTime;

                }
                else{
                    Donot_return = true;
                    launchAngle = 75;
                    float radians = launchAngle * 3.14159265 / 180.0;
                    float horizontalVelocity = initialVelocity * cos(radians);
                    float verticalVelocity = initialVelocity * sin(radians) - gravity * deltaTime;
                    x_ball -= horizontalVelocity * deltaTime;
                    y_ball -= verticalVelocity * deltaTime;
//                    std::cout<<x_ball;

                    if (y_ball < -10.5)
                    {

                        y_ball = -10.5;
                        move = true;
                        move_ball(1);
                        animation_ball = 0;
                    }
    }



    }



    glutPostRedisplay();
    glutTimerFunc(animate_time, animate_ball, 1);

}


void animation(int value)
{
    if (animate)
    {
        // Update the right arm angle from 180 to 45 degrees
        leftArmAngle -= 1.0;

        if (leftArmAngle < 225.0)
        {
            leftArmAngle = 225.0;
            animate = 0;  // Stop the animation when the desired angle is reached.
            initialVelocity = 100;
            launchAngle = 35;

            animate_ball(1);



        }

        glutPostRedisplay();
        glutTimerFunc(animate_time, animation, 0);

    }
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;

        case ' ':
            if (animate)
            {
                animate = 0;
            }
            else
            {
                animate = 1;
                animation(1);
            }
            break;


        case 'x':
            Xangle += 5.0;
            if (Xangle > 360.0) Xangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'X':
            Xangle -= 5.0;
            if (Xangle < 0.0) Xangle += 360.0;
            glutPostRedisplay();
            break;
        case 'y':
            Yangle += 5.0;
            if (Yangle > 360.0) Yangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Y':
            Yangle -= 5.0;
            if (Yangle < 0.0) Yangle += 360.0;
            glutPostRedisplay();
            break;
        case 'z':
            Zangle += 5.0;
            if (Zangle > 360.0) Zangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Z':
            Zangle -= 5.0;
            if (Zangle < 0.0) Zangle += 360.0;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

//    glutInitContextVersion(4, 3);
//    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("box.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();



    setup();

    glutMainLoop();
}

