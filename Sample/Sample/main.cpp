#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>

//Global decalarations

int switchTransitionFinished=0;
int choosenCupRegion;
int startBottomtoTopAnimation=0;
float speedToptoDownAnimation=0.0025f;
int showBall=1;
int ballContainerCupIndex=1;
int startGame=0;
int animationTypeFlag;
int nSwitches=10;
int finalBallPosSet=0;
int gameModeSubMenu;
int subMenu;
int level=1;
int switchSpeed;

//lightings and intensities (r,g,b,A);
GLfloat colorText[]={1,1,0,1};
GLfloat colorGameOverText[]={0,1,0,1};
GLfloat colorBase[]={1,1,1,1};
GLfloat colorBall[]={0.55,0.09,0.09,1};
GLfloat colorCups[]={0.137255,0.419608 ,0.556863,1};

GLfloat qaAmbientLight[]    = {0.2, 0.2, 0.2, 1.0};
GLfloat qaDiffuseLight[]    = {0.8, 0.8, 0.8, 1.0};
GLfloat qaSpecularLight[]    = {1.0, 1.0, 1.0, 1.0};

GLfloat qaLightPosition[]    = {15,15,-3.5};               //Position of the light source



//Standard colors
GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color


//orient the scene for proper viewing of the screen
void orientScene()
{
           //(0, x,y,z)
    glRotated(50,0,1,0);            // Pivot  :  left(-angle)  or   Right(+angle)                 rotates about y-axis
    glRotated(10,-1,0,0);          //  Turn   :  Up(+angle)    or   Down(-angle)                  rotates about x-axis
    glRotated(11.7,0,0,-1);       // Submerge :  left(-angle)  or   Right(+angle)                 rotates about z-axis
}

class Vector3
{
public:
    float x;
    float y;
    float z;
};

//class to handle ball
class BallHandler
{
Vector3 pos;
int cupId;

public:
    BallHandler()
    {
    pos.x=0.2;
    pos.y=-1.1;
    pos.z=0;
    }
    //setters
    void setPosX(float x){
            pos.x=x;
    }

    void setPosY(float y){
            pos.y=y;
    }
    
    void setPosZ(float z){
            pos.z=z;
    }

    //getters
    float getPosX(){
            return pos.x;
    }
    float getPosY(){
            return pos.y;
    }
    float getPosZ(){
            return pos.z;
    }

    void displayBall()
    {
        //reset the cordinate system
        glLoadIdentity();

        orientScene();

        // Set material properties and color for ball
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorBall);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorBall);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);

        //transalate to proper position
        glTranslated(pos.x,pos.y,pos.z);
        glScaled(1,1.2,1);

        //create the sphere
        glutSolidSphere(0.1, 40.0, 40.0);
        
    }

};

//class to handle Cup
class CupHandler
{
Vector3 pos;
int cupRegionId;
int switchTransition;
public:
    CupHandler()
    {pos.x=0;
    pos.y=0;
    pos.z=0;
    switchTransition=1;
    }
    CupHandler(int x,int y,int z)
    {
    pos.x=x;
    pos.y=y;
    pos.z=z;
    switchTransition=1;
    }
    
    //setters
    void setPosX(float x){
            pos.x=x;
    }

    void setPosY(float y){
            pos.y=y;
    }
    
    void setPosZ(float z){
            pos.z=z;
    }

    //getters
    float getPosX(){
            return pos.x;
    }
    float getPosY(){
            return pos.y;
    }
    float getPosZ(){
            return pos.z;
    }

    void displayCup()
    {
        
        //reset the cordinate system
        glLoadIdentity();
        
        orientScene();

        // Set material properties and color for ball
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorCups);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorCups);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);

        
        //trasalate to proper position
        glTranslated(pos.x,pos.y,pos.z);
                
        //creates a frustum
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();

        // rotate the frustum along y axis
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadratic,0.2f,0.16f,0.5f,50,50);

            
    }
    
    //used for ball cover animation (top to down cup movement)
    void updateYPos()
    {
        //decide between top to bottom or bottom to top animation
        if(switchTransitionFinished!=1)
        {
            if(pos.y>-1.2)
                pos.y-=speedToptoDownAnimation;         //bring cups down
            else
                animationTypeFlag=1;
        }
        else
        {
            if(pos.y<0)
                pos.y+=speedToptoDownAnimation;         //lift the cups
            else
                animationTypeFlag=2;
        }
    }

    int getRegion()
    {
        return cupRegionId;
    }
    
    void setRegion(int reg)
    {
        cupRegionId=reg;;
    }
    
};

BallHandler ball;
CupHandler cups[3];

//set game Params : Animation speed and no.of shuffles of cups

void setGameLevelParameters()
{
    switch(level)
    {
    case 1: switchSpeed=100;
            nSwitches=5;
        break;
    case 2: switchSpeed=75;
            nSwitches=5;
        break;
    case 3: switchSpeed=50;
            nSwitches=10;
        break;
    case 4:switchSpeed=40;
            nSwitches=15;
            break;
    }

}



// create cuboid on which balls will be placed

void createCuboid(double tx,double ty,double tz,double sx,double sy,double sz)
{
     orientScene();

     glTranslated(tx,ty,tz);
     glScaled(sx,sy,sz);
     glutSolidCube(1);                      //size of the cubiod = 1
     glLoadIdentity();
}

// Display functions

void drawStrokeText(char*string,float x,float y,float z,float sx,float sy,float sz)
{
      char *c;
      glPushMatrix();
      glTranslatef(x,y,z);
      glScalef(sx,sy,sz);
  
      for (c=string; *c != '\0'; c++)
            glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
    
      glPopMatrix();
}

void displayCupNumbers()
{
    // Set material properties and color for texts
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorGameOverText);     // (?)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorGameOverText);     //spread over
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorGameOverText);    //mirror-like properties
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
        
    drawStrokeText("Choose a Cup.....",-1,0.3,0,0.002,0.001,0.0005);
    orientScene();

    // Set material properties and color for texts
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorText);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);

    drawStrokeText("1",1.2,-0.4,0,0.002,0.001,0.0005);
    drawStrokeText("2",0.2,-0.4,0,0.002,0.001,0.0005);          //TO DO : experiment
    drawStrokeText("3",-0.8,-0.4,0,0.002,0.001,0.0005);
    
    glLoadIdentity();
}

void displayGameOverText()                                      // TO DO : check once more
{
    int ballContainerCupRegion = cups[ballContainerCupIndex].getRegion();

    if(ballContainerCupRegion == choosenCupRegion)
    {
        // Set material properties and color for texts
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorGameOverText);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorGameOverText);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorGameOverText);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);

        drawStrokeText("You Win...",-0.7,-1,0,0.0021,0.0016,0.0005);
    }
    else
    {
        // Set material properties and color for texts
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorGameOverText);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorGameOverText);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorGameOverText);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);

        drawStrokeText("You Lose...",-0.7,-1,0,0.0021,0.0016,0.0005);
    }
}

void display()
{
    glViewport(80,40,1000,800);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Set material properties and color for texts
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorText);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);       //TO DO : experiment

    glLineWidth(5);                                         //TO DO : experiment
    drawStrokeText("Cup and Ball Game", -2.0, 1 , 0 , 0.0028,0.002,0.001);
                                     // x  , y  , z  , sx,    sy,    sz

    //displays the cup numbers
    if(switchTransitionFinished==1 && startBottomtoTopAnimation==0)
    {
        glLineWidth(3);
        displayCupNumbers();
    }

    if(startBottomtoTopAnimation==1)
        displayGameOverText();

    // Set material properties and color for ball
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorBase);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorBase);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorBase);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    
    //creates the table on which the balls and cups will be placed
    createCuboid(0.2,-1.3, -0.2, 3, 0.05, 3);
               // tx,  ty,  tz, sx, sy,  sz
     
    if(showBall==1)         //displays the ball
        ball.displayBall();
    
    //display the cups
    cups[0].displayCup();
    cups[1].displayCup();
    cups[2].displayCup();

    glFlush();
    glutSwapBuffers();
    
    glLoadIdentity();
}

void displayCoverPage()
{
    glViewport(80,40,1000,800);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorGameOverText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorGameOverText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorGameOverText);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    drawStrokeText("Computer Graphics Project", -2.0, 1 , 0 , 0.0015,0.002,0.001);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorText);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorText);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    drawStrokeText("Cup and Ball Game", -1.5, 0.5 , 0 , 0.0015,0.002,0.001);
    glLineWidth(2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorBase);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorBase);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorBase);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    drawStrokeText("Deepak Kumar P Honakeri - 1PE17CS044", -2.0, 0, 0, 0.001, 0.001, 0.0001);
    drawStrokeText("Hrishikesh Kumar       - 1PE17CS060", -2.0, -0.3, 0, 0.001, 0.001, 0.0001);
    
 
    glFlush();
    glutSwapBuffers();
}

// Shuffle the cups
void cupSwitchAnimation(int cupTag1,int cupTag2,int direction)          //TO DO : check once more
{
    
        float tempPosX=cups[cupTag1].getPosX();
        float tempPosZ=cups[cupTag1].getPosZ();

        float tempPosX2=cups[cupTag2].getPosX();
        float tempPosZ2=cups[cupTag2].getPosZ();

        float r=(cups[cupTag1].getPosX()-cups[cupTag2].getPosX())/2;

        setGameLevelParameters();
                        
        for(int i=0;i<switchSpeed;i++)
             {
                         
              float theta=3.1415926*float(i)/float(switchSpeed);
              float x=r*cosf(theta);
              float z=r*sinf(theta);
              
              cups[cupTag1].setPosX(tempPosX+x-r);
              cups[cupTag2].setPosX(tempPosX2-x+r);
                 
              
              if(direction==1){
              cups[cupTag1].setPosZ(tempPosZ+z);
              cups[cupTag2].setPosZ(tempPosZ2-z);
              printf("(%f,%f)\n",tempPosX+x-r,tempPosZ+z);
              }
              else
              {
              cups[cupTag1].setPosZ(tempPosZ-z);
              cups[cupTag2].setPosZ(tempPosZ2+z);
              //printf("(%f,%f)\n",(tempPosX+x-r,tempPosZ-z));
              }

              //call the display function again
              display();
             }
    
        //finally exchange the cup region ids
        int tmp=cups[cupTag1].getRegion();
        cups[cupTag1].setRegion(cups[cupTag2].getRegion());
        cups[cupTag2].setRegion(tmp);
}

//keyboard Functions
void keys(unsigned char key,int x,int y)
{
    if(switchTransitionFinished==1&&choosenCupRegion==0)
    {
        switch(key)
        {
        case '1':startBottomtoTopAnimation=1;choosenCupRegion=1;
            break;
        case '2':startBottomtoTopAnimation=1;choosenCupRegion=2;
            break;
        case '3':startBottomtoTopAnimation=1;choosenCupRegion=3;
            break;
        }
    
    }
 
}

// sets ball position
void setFinalBallPos()
{
    ball.setPosX(cups[ballContainerCupIndex].getPosX());
    ball.setPosZ(cups[ballContainerCupIndex].getPosZ());

    printf("cup index = %d",ballContainerCupIndex);
    finalBallPosSet=1;
}

// idleFunc : function called before display() and when theres no user interaction
void idleFunc(void)
{
    if(startGame==1)
    {
        if(animationTypeFlag==0)
        {
            //top to bottom animation
            cups[0].updateYPos();
            cups[1].updateYPos();
            cups[2].updateYPos();
        }
        
        else if(animationTypeFlag==1)
        {
            //hide the ball during switch(shuffle) transition
            showBall=0;
            
            if(switchTransitionFinished==0)
            {
                for(int i=0;i<nSwitches;i++)
                {
                    int cup1Index=rand()%3;
                    int cup2Index=rand()%3;
                
                    //set direction of cup movement
                    int direction;
                    
                    switch(rand()%2)
                        {
                        case 0:direction=-1;        //clockwise
                            break;
                        case 1:direction=1;         //anti-clockwise
                            break;
                        }
            
                    //ensure the cup index are not the same
                    while(cup1Index==cup2Index)
                        cup2Index=rand()%3;

                    cupSwitchAnimation(cup1Index,cup2Index,direction);
                }
            }
            //signifies that switch transition is done
            switchTransitionFinished=1;
            showBall=1;
            animationTypeFlag=2;
        }
        
        else
        {
            if(finalBallPosSet==0)      //set the position of the ball to the cup that contains it
                setFinalBallPos();

            //if any cup is selected
            if(startBottomtoTopAnimation)
            {
                //bottom to top animation
                cups[0].updateYPos();
                cups[1].updateYPos();
                cups[2].updateYPos();
            }

            
        }
        display();
    }
}

//init functions

void initGameBeginState()
{
    //set the initial postions of the cups
    cups[0].setPosX(1.2);
    cups[0].setPosY(0);        //front cup
    cups[0].setPosZ(0);

    cups[1].setPosX(0.2);
    cups[1].setPosY(0);        //middle cup
    cups[1].setPosZ(0);

    cups[2].setPosX(-0.8);
    cups[2].setPosY(0.0);        //back Cup
    cups[2].setPosZ(0);

    //initial ball pos
    ball.setPosX(0.2);
    ball.setPosY(-1.0);
    ball.setPosZ(0);

    //set the regions of the balls
    cups[0].setRegion(1);
    cups[1].setRegion(2);
    cups[2].setRegion(3);
    
    //initialize variables
     speedToptoDownAnimation=0.010f;
     animationTypeFlag=0;
     nSwitches=10;
     switchTransitionFinished=0;
     showBall=1;
     ballContainerCupIndex=1;
     finalBallPosSet=0;
     startBottomtoTopAnimation=0;
     choosenCupRegion=0;
}


void myinit()
{
 //intial state
 initGameBeginState();
 glClearColor(0.6,0.6,0.6,1);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-2,2,-2,2,4,-4);
 glMatrixMode(GL_MODELVIEW);
}

void initLighting()
{

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    
    // Set the light position
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

}

//Menus

void main_menu(int id)
{
 switch(id)
    {case 3 : level=1;
              break;
     case 4 :level=2;
              break;
     case 5 : level=3;
              break;
     case 6 : level=4;
              break;
    }
}
void top_menu(int id)
{
    switch(id)
    {
        case 0:startGame=1;
              initGameBeginState();
              break;
        case 1 : main_menu(id);
              break;
        case 2 : exit(0);
              break;
    }
}

void init_menu(int id)
{
    switch(id)
    {
        case 0:  displayCoverPage();
                 break;
        case 1 : top_menu(id);
                 break;
    }
}


int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1000,700);
    glutCreateWindow("Cup and Ball 3D");
    
    glutKeyboardFunc(keys);         //call backs
    glutDisplayFunc(display);       //call backs
    glutIdleFunc(idleFunc);         //call backs
    
    initLighting();
    myinit();
    
    glEnable(GL_DEPTH_TEST);
    
    //create Menu
    gameModeSubMenu=glutCreateMenu(main_menu);
    glutAddMenuEntry("Easy",3);
    glutAddMenuEntry("Medium",4);
    glutAddMenuEntry("Hard",5);
    glutAddMenuEntry("Very Hard",6);

       
    subMenu = glutCreateMenu(top_menu);
    glutAddMenuEntry("Start Game",0);
    glutAddSubMenu("Difficulty",gameModeSubMenu);
    glutAddMenuEntry("Quit",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
       
    glutCreateMenu(init_menu);
    glutAddMenuEntry("Project Cover",0);
    glutAddSubMenu("Game",subMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    return 0;
}

/*notes
  http://math.hws.edu/bridgeman/courses/324/s06/doc/opengl.html#lights
 
 **************************        main()          ****************************************
 
 glutDisplayFunc() : a callback function whenever the display has to be refreshed like window resized, minimized, etc. and doesn't call the display                   function but  it just registers it so that future display needs will invoke the callback.
 
 glutReshapeFunc() : is similar to glutDisplayFunc in that it sets up a callback - this time, the callback is the function to call when the window is                   reshaped (i.e. resized).
 
 glutMainLoop() : it tells the program to ENTER in GLUT event processing loop (meaning that it sit and waits for the any event to occur)
 
 glFlush() : just clears all the drawing commands. OpenGL basically stores caches all the commands on a buffer and not displayed until it is flushed

 
 
 *************************              GL_PROJECTION and GL_MODELVIEW     *******************
 
 GL_PROJECTION : projection tranformations
 GL_MODELVIEW : model and viewing transformations
 
 
 ************************* DEPTH BUFERING           **********************
 
 open GL doesn't do proper rendering of  3-D objects for lighting and materials
 
 so specify- GL_DEPTH
 
 
 ***************    CYLINDER        ************
 
 gluCylinder(gluNewQuadric(),base,top,height,slices,stacks);        -draws along z-axis from
 
                z=0 to z=height
                base, top : are radius' (setting anyone =0 ----->  cone)
                slices/stakcs : subdivisions of the cylinder , the more the "finer" the object is rendered and takes more time
 
 
 glutSolidSphere(radius,slices,stacks);
 
*/
