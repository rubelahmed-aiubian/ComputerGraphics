#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

//moving speed
float speed=0.0;
float plane_speed=0.0;
//rain variable
bool israining=false;
float rainposition_y=0.0;

//car variable
float carposition_x=0.0;
float carposition_y=0.0;
float carposition_z=0.0;

//boat variable
float boatposition_x = 0.0;
float boatposition_y = 0.0;
float boatposition_z = 0.0;

//cloud variable
float cloudoneposition_x=0.0;
float cloudtwoposition_x=0.0;
float cloudthreeposition_x=0.0;

//frame width
float width=-940;
float width2=600;
float width3=2000;

// night variable
int nightflag = 0;
bool isnight = false;

//sky color
int skyred=150;
int skygreen=227;
int skyblue=250;

//hill color
int hillred=191;
int hillgreen=180;
int hillblue=119;

int smallhillred=184;
int smallhillgreen=174;
int smallhillblue=118;

//lamp post color
int lampostred=255;
int lampostgreen=252;
int lampostblue=209;

//sun color
int sunred=246;
int sungreen=171;
int sunblue=26;

//cloud color
int cloudred=230;
int cloudgreen=234;
int cloudblue=237;

//above road color
int uproadred=255;
int uproadgreen=227;
int uproadblue=150;

//down road color
int downroadred=255;
int downroadgreen=219;
int downroadblue=117;

//sea color
int seared = 52;
int seagreen = 194;
int seablue = 237;

//Display Instructions
char b[] = "s = start move & Increase Speed";
char n[] = "n = Night/Day";
char e[] = "e = Exit.";
char rain[] = "Right click for Rain";

//initialization
void myInit (void)
{
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glColor3f(0.0f, 0.0f, 0.0f);
        glPointSize(4.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 902.0, 0.0, 684.0);
}

//Display Instructions
void print( float x, float y, char *st)
{
    int length, i;

    length=strlen( st );

    glColor3f(0, 0, 0);
    if(isnight)
    {
        glColor3f(255, 255, 255);
    }

    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < length; i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }
}

//Draw Circle
void drawCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    int i;
    int triangleAmount = 50; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * 3.1416;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2d(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
        glEnd();
}

//Draw Sky
void Sky()
{
        glPushMatrix();
        glColor3ub(skyred,skygreen,skyblue);
        glBegin(GL_QUADS);
        glVertex2i(0,684);
        glVertex2i(902,684);
        glVertex2i(902,0);
        glVertex2i(0,0);
        glEnd();
        glPopMatrix();

        glutPostRedisplay();
}

void star()
{
    for(int i=1; i<20*50; i+=50 )
    {
        for(int j=0; j <20*50; j+=20)
        {
            glColor3ub(255, 255, 255);
            drawCircle(-70+i+j,603+j,1);
        }
    }
}

//Draw Moon
void Moon()
{
    glPushMatrix();
    glColor3ub(255, 255, 255);
    drawCircle(824.0f,615.0f,40.0f);
    if(isnight)
    {
        glColor3ub(skyred, skygreen, skyblue);
    }
    drawCircle(834.0f,635.0f,40.0f);
    glPopMatrix();
}

//Draw Sun
void Sun()
{
    glColor3ub(sunred, sungreen, sunblue);
    drawCircle(824.0f,615.0f,40.0f);
    glutPostRedisplay();
}

//Draw Clouds
void Cloud()
{
    glPushMatrix();
    glTranslatef(speed+cloudoneposition_x,0,0);
    glColor3ub(cloudred,cloudgreen,cloudblue);
    drawCircle(594.0f,586.0f,20.0f);
    drawCircle(572.0f,595.0f,28.0f);
    drawCircle(539.0f,595.0f,35.0f);
    drawCircle(513.0f,575.0f,20.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(speed+cloudtwoposition_x,0,0);
    drawCircle(393.0f,577.0f,20.0f);
    drawCircle(370.0f,585.0f,28.0f);
    drawCircle(339.0f,583.0f,35.0f);
    drawCircle(311.0f,565.0f,20.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(speed+cloudthreeposition_x,0,0);
    drawCircle(193.0f,607.0f,20.0f);
    drawCircle(170.0f,615.0f,28.0f);
    drawCircle(139.0f,613.0f,35.0f);
    drawCircle(111.0f,595.0f,20.0f);
    glPopMatrix();
}

//Draw Sea
void sea()
{
    glPushMatrix();
    glColor3ub(seared, seagreen, seablue);
    glBegin(GL_QUADS);
    glVertex3f(0.0,258.0,0.0);
    glVertex3f(902.0,258.0,0.0);
    glVertex3f(902.0,400.0,0.0);
    glVertex3f(0.0,400.0,0.0);
    glEnd();
    glPopMatrix();
}

void boat()
{
    int x_axis = 100;
    int y_axis = 400;

    glPushMatrix();

    glTranslatef(speed+boatposition_x,boatposition_y, boatposition_z);

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);

    glVertex2f(-10+ x_axis, -85+ y_axis);
    glVertex2f(25+ x_axis,-85+ y_axis);
    glVertex2f(30+ x_axis,-80+ y_axis);
    glVertex2f(-15+ x_axis,-80+ y_axis);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub( 125, 10, 171  );

    glVertex2f(-10+ x_axis,-80+ y_axis);
    glVertex2f(10+ x_axis,-80+ y_axis);
    glVertex2f(10+ x_axis,-70+ y_axis);
    glVertex2f(-10+ x_axis,-70+ y_axis);
    glEnd();
    glPopMatrix();
}

void ship()
{
    int x_axis = 500;
    int y_axis = 380;

    glPushMatrix();
    glTranslatef(speed+boatposition_x, boatposition_y, boatposition_z);
    GLfloat w=0.0;
    glColor3ub(0,0,0 );
    glBegin(GL_POLYGON);

    glVertex2f(35+x_axis,-65+y_axis);
    glVertex2f(70+x_axis,-65+y_axis);
    glVertex2f(75+x_axis,-60+y_axis);
    glVertex2f(30+x_axis,-60+y_axis);
    glEnd();

    glBegin(GL_POLYGON);//  boat 2 body 2
    glColor3ub(249, 130, 3 );

    glVertex2f(35+x_axis,-60+y_axis);
    glVertex2f(70+x_axis,-60+y_axis);
    glVertex2f(60+x_axis,-50+y_axis);
    glVertex2f(45+x_axis,-50+y_axis);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub( 253, 254, 254  );

    glVertex2f(45+x_axis,-58+y_axis);
    glVertex2f(50+x_axis,-58+y_axis);
    glVertex2f(50+x_axis,-53+y_axis);
    glVertex2f(45+x_axis,-53+y_axis);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub( 253, 254, 254  );

    glVertex2f(55+x_axis,-58+y_axis);
    glVertex2f(60+x_axis,-58+y_axis);
    glVertex2f(60+x_axis,-53+y_axis);
    glVertex2f(55+x_axis,-53+y_axis);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub( 0,0,0 );

    glVertex2f(-80+x_axis,-45+y_axis);
    glVertex2f(-50+x_axis,-45+y_axis);
    glVertex2f(-45+x_axis,-40+y_axis);
    glVertex2f(-85+x_axis,-40+y_axis);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub( 241, 196, 15  );

    glVertex2f(-80+x_axis,-40+y_axis);
    glVertex2f(-50+x_axis,-40+y_axis);
    glVertex2f(-50+x_axis,-36+y_axis);
    glVertex2f(-80+x_axis,-36+y_axis);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub( 222, 49, 99 );

    glVertex2f(-75+x_axis,-36+y_axis);
    glVertex2f(-55+x_axis,-36+y_axis);
    glVertex2f(-55+x_axis,-33+y_axis);
    glVertex2f(-75+x_axis,-33+y_axis);
    glEnd();
    glPopMatrix();
}

void hill()
{
    for(int i=0; i<7*130;i+=130)
    {
        //small hill
        glPushMatrix();
        glColor3ub(smallhillred, smallhillgreen, smallhillblue);
        glBegin(GL_TRIANGLES);
        glVertex2i(85+i,400);
        glVertex2i(150+i,400);
        glVertex2i(117.5+i,450);
        glEnd();
        glPopMatrix();

        //big hill
        glPushMatrix();
        glColor3ub(hillred, hillgreen, hillblue);
        glBegin(GL_TRIANGLES);
        glVertex2i(0+i,400);
        glVertex2i(100+i,400);
        glVertex2i(50+i,500);
        glEnd();
        glPopMatrix();
    }
}

//Upper side of road
void uproadside()
{
    for(int i=0;i<16*60;i+=30)
    {
        glPushMatrix();
        glColor3ub(255,255,255);
        glBegin(GL_QUADS);
        glVertex2i(0+i,148);
        glVertex2i(16+i,148);
        glVertex2i(16+i,157);
        glVertex2i(0+i,157);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(16+i,148);
        glVertex2i(39+i,148);
        glVertex2i(39+i,157);
        glVertex2i(16+i,157);
        glEnd();
        glPopMatrix();
    }
}

//Draw Road
void Road()
{
    glPushMatrix();
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
    glVertex2i(0,148);
    glVertex2i(902,148);
    glVertex2i(902,47);
    glVertex2i(0,47);
    glEnd();
    glPopMatrix();

    for(int i=0;i<120*8;i+=120)
    {
        glPushMatrix();
        glColor3ub(255,255,255);
        glBegin(GL_QUADS);
        glVertex2i(0+i,95);
        glVertex2i(35+i,95);
        glVertex2i(35+i,100);
        glVertex2i(0+i,100);
        glEnd();
        glPopMatrix();
    }
}

//Down side of road
void downroadside()
{
    for(int i=0;i<16*60;i+=30)
    {
        glPushMatrix();
        glColor3ub(255,255,255);
        glBegin(GL_QUADS);
        glVertex2i(0+i,148-100);
        glVertex2i(16+i,148-100);
        glVertex2i(16+i,157-100);
        glVertex2i(0+i,157-100);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(16+i,148-100);
        glVertex2i(39+i,148-100);
        glVertex2i(39+i,157-100);
        glVertex2i(16+i,157-100);
        glEnd();
        glPopMatrix();
    }
}

//bottom side of road
void downroadsand()
{
    glPushMatrix();
    glColor3ub(downroadred, downroadgreen, downroadblue);
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(902.0,0.0,0.0);
    glVertex3f(902.0,47.0,0.0);
    glVertex3f(0.0,47.0,0.0);
    glEnd();
    glPopMatrix();
}

//upside of road
void uproadsand()
{
    glPushMatrix();
    glColor3ub(uproadred, uproadgreen, uproadblue);
    glBegin(GL_QUADS);
    glVertex3f(0.0,157.0,0.0);
    glVertex3f(902.0,157.0,0.0);
    glVertex3f(902.0,258.0,0.0);
    glVertex3f(0.0,258.0,0.0);
    glEnd();
    glPopMatrix();
}

void umbrella()
{
    for(int i=0; i<5*200; i+=180)
    {
        glPushMatrix();
        glColor3ub(255, 255, 28);
        glBegin(GL_TRIANGLES);
        glVertex2i(60+i,280);
        glVertex2i(140+i,280);
        glVertex2i(100+i,300);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(97, 97, 97);
        glBegin(GL_QUADS);
        glVertex2i(98+i,220);
        glVertex2i(102+i,220);
        glVertex2i(102+i,280);
        glVertex2i(98+i,280);
        glEnd();
        glPopMatrix();
    }
}

//Draw Trees
void Tree()
{
    for(int i=0; i<7*130;i+=130)
    {
        glPushMatrix();
        glColor3ub(37,90,27);
        glBegin(GL_TRIANGLES);
        glVertex2i(24+i,46);
        glVertex2i(67+i,46);
        glVertex2i(46+i,78);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(37,90,27);
        glBegin(GL_TRIANGLES);
        glVertex2i(24+i,40);
        glVertex2i(67+i,40);
        glVertex2i(46+i,72);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(161,89,61);
        glBegin(GL_QUADS);
        glVertex2i(39+i,40);
        glVertex2i(52+i,40);
        glVertex2i(52+i,0);
        glVertex2i(39+i,0);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(37,90,27);
        glBegin(GL_TRIANGLES);
        glVertex2i(24+i,32);
        glVertex2i(67+i,32);
        glVertex2i(46+i,64);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(37,90,27);
        glBegin(GL_TRIANGLES);
        glVertex2i(24+i,24);
        glVertex2i(67+i,24);
        glVertex2i(46+i,56);
        glEnd();
        glPopMatrix();
    }
}

//Draw Lam Post
void LampPost()
{
    for(int i=0;i<8*115;i+=125)
    {
        glPushMatrix();
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(34+i,158);
        glVertex2i(51+i,158);
        glVertex2i(51+i,160);
        glVertex2i(34+i,160);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(37+i,160);
        glVertex2i(48+i,160);
        glVertex2i(48+i,162);
        glVertex2i(37+i,162);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(40+i,162);
        glVertex2i(45+i,162);
        glVertex2i(45+i,206);
        glVertex2i(40+i,206);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(38+i,206);
        glVertex2i(48+i,206);
        glVertex2i(48+i,209);
        glVertex2i(38+i,209);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(lampostred,lampostgreen,lampostblue);
        drawCircle(42.5+i,221,12);
        glPopMatrix();
    }
}

//Moving Car
void Car()
{
    glPushMatrix();
    glTranslatef(carposition_x, carposition_y, carposition_z);
    glColor3ub(234,56,78);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(459+500,154-70);
    glVertex2i(466+500,160-70);
    glVertex2i(491+500,160-70);
    glVertex2i(510+500,179-70);
    glVertex2i(568+500,179-70);
    glVertex2i(579+500,162-70);
    glVertex2i(579+500,141-70);
    glVertex2i(459+500,141-70);
    glEnd();

    glColor3ub(155,186,189);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(503+500,169-70);
    glVertex2i(512+500,177-70);
    glVertex2i(525+500,177-70);
    glVertex2i(521+500,163-70);
    glVertex2i(503+500,163-70);
    glEnd();

    glColor3ub(155,186,189);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(526+500,163-70);
    glVertex2i(530+500,177-70);
    glVertex2i(547+500,177-70);
    glVertex2i(547+500,163-70);
    glEnd();

    glColor3ub(155,186,189);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(552+500,163-70);
    glVertex2i(551+500,177-70);
    glVertex2i(561+500,177-70);
    glVertex2i(570+500,163-70);
    glEnd();

    glColor3ub(51,53,50);
    drawCircle(474+500,142-70,10);
    glColor3ub(255,0,0);
    drawCircle(474+500,142-70,8);
    glColor3ub(0,0,0);
    drawCircle(474+500,142-70,7);

    glColor3ub(51,53,50);
    drawCircle(551+500,142-70,10);
    glColor3ub(255,0,0);
    drawCircle(551+500,142-70,8);
    glColor3ub(0,0,0);
    drawCircle(551+500,142-70,7);

    glPopMatrix();
}

//Draw rain
void Rain()
{
    glPushMatrix();
    glTranslatef(speed,(-1)*rainposition_y,0);
    cout << "Rain speed: "  << speed*1 << endl;
    glColor3ub(255, 255, 255);
    for(int j=0;j<20*160;j+=20)
    {
        for(int i=0;i<20*160;i+=20)
        {
            glBegin(GL_LINES);
            glVertex2f(0+i+j,0+i);
            glVertex2f(-4+i+j,10+i);
            glEnd();

            glBegin(GL_LINES);
            glVertex2f(0+i-j,0+i);
            glVertex2f(-4+i-j,10+i);
            glEnd();
        }
    }
    glPopMatrix();
}

//Raining mode
void Raining()
{
    if(israining == false)
    {
        israining = true;
        PlaySound("rain.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

    }else
    {
        israining = false;
        PlaySound(NULL, 0, 0);
    }
}

//Moving Plane
void Plane()
{
    glPushMatrix();
    glTranslatef(plane_speed,0.0,0.0);
    glColor3ub(0,78,168);
    glBegin(GL_QUADS);
    glVertex2i(7-200,307+350);
    glVertex2i(76-200,318+350);
    glVertex2i(95-200,312+350);
    glVertex2i(22-200,290+350);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(13-200,305+350);
    glVertex2i(0-200,338+350);
    glVertex2i(4-200,339+350);
    glVertex2i(25-200,313+350);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(32-200,277+350);
    glVertex2i(49-200,301+350);
    glVertex2i(64-200,306+350);
    glVertex2i(37-200,279+350);
    glEnd();

    int j=0;
    for(int i=0;i<5*10;i+=10)
    {
        glColor3ub(249,190-j,0);
        drawCircle(73-i-200,312.5-j+350,2);
        j+=2;
    }

    glPopMatrix();
}

//Car moving function
void CarTranslate(int value)
{
    width+=1.0;
    width2-=1.0;

    if(width<10093)
    {
        cloudoneposition_x+=0.0001;
        cloudtwoposition_x+=0.0003;
        cloudthreeposition_x+=0.0002;
        boatposition_x += 0.0001;

        speed+=0.05;
        plane_speed+=1.0;

        if(width>10091)
        {
            width=-940;
            speed=0.0;
        }
        cout << "Width: " << width << endl;
    }
    if(width2>-1614)
    {
        carposition_x-=0.5;
        rainposition_y+=0.6;
        if(width2==-1613)
        {
            width2=600;
            carposition_x=0;
            rainposition_y=0;
        }
        cout << "Width2: " << width2 << endl;
    }
    glutTimerFunc(value, CarTranslate, 25);
}

//Night Mode On
void nightmode()
{
            skyred=0;
            skygreen=50;
            skyblue=59;

            hillred=112;
            hillgreen=107;
            hillblue=77;

            smallhillred=99;
            smallhillgreen=95;
            smallhillblue=71;

            lampostred=255;
            lampostgreen=255;
            lampostblue=255;

            sunred=0;
            sungreen=50;
            sunblue=59;

            cloudred=0;
            cloudgreen=50;
            cloudblue=59;

            uproadred=255;
            uproadgreen=213;
            uproadblue=94;

            downroadred=255;
            downroadgreen=213;
            downroadblue=94;
}

//Day Mode On
void daymode()
{
            skyred=103;
            skygreen=155;
            skyblue=176;

            hillred=191;
            hillgreen=180;
            hillblue=119;

            smallhillred=184;
            smallhillgreen=174;
            smallhillblue=118;

            lampostred=235;
            lampostgreen=235;
            lampostblue=235;

            sunred=246;
            sungreen=171;
            sunblue=26;

            cloudred=230;
            cloudgreen=234;
            cloudblue=237;

            uproadred=255;
            uproadgreen=227;
            uproadblue=150;

            downroadred=255;
            downroadgreen=219;
            downroadblue=117;

}

void bird()
{
    for(int j=50; j>0; j-=15)
    {
        for(int i=0; i<j; i+=15)
        {
            glPushMatrix();
            glColor3ub(0.0,0.0,0.0);
            glBegin(GL_LINES);
            glVertex2f(800.0+i,550.0+j);
            glVertex2f(810.0+i,555.0+j);

            glVertex2f(810.0+i,550.0+j);
            glVertex2f(800.0+i,555.0+j);
            glEnd();
            glPopMatrix();
        }
    }
}

//Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        //start movement
        case 's':
            CarTranslate(0);
            break;

        //night mode
        case 'n':
            nightflag += 1;

            if(nightflag % 2 != 0)
            {
                nightmode();
                isnight = true;
            }
            else
            {
                daymode();
                isnight = false;
            }

            break;

        //exit application
        case 'e':
            exit(1);
            break;
    }
}

//Mouse Function
void mouse(int button,int state,int x,int y)
{
    switch(button)
    {
    case GLUT_RIGHT_BUTTON:
        if(state==GLUT_DOWN)
        Raining();
        break;
    default:
        break;
    }
}

//Display Object
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    Sky();
    Cloud();
    if(isnight){if(israining == false) star();}
    sea();
    ship();
    boat();
    Sun();
    if(isnight == false)bird();
    if(isnight)Moon();
    hill();
    uproadsand();
    downroadsand();
    Road();
    downroadside();
    umbrella();
    LampPost();
    uproadside();

    Car();
    Tree();
    Plane();

    if(israining) Rain();

    //Display Instructions
    print(30,530,b);
    print(30,500,n);
    print(30,470,rain);
    print(30,440,e);

    glFlush ();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1200,800);
    glutInitWindowPosition (250, 30);
    glutCreateWindow ("Sea Site View");
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    myInit ();
    glutMainLoop();
}
