#include <iostream>
#include <glut.h>
#define WIDTH 600
#define HEIGHT 600

double arr[5000][4];
int z=0;
int flag=0;
float radius=0.03;
int ptr=0;
float color[3][3]={{1.0,1.0,1.0},{1.0,1.0,0.0},{0.0,1.0,0.0}};

void init()
{
    glClearColor( 0.0, 0.0, 0.0, 1.0);
    glMatrixMode( GL_PROJECTION);
    gluOrtho2D(0.0,WIDTH,0.0,HEIGHT);
    glPointSize(20.0);
}

void resetAll()
{
    z=0;
}

float getOpenGLX(int x)
{
    double ox = x/ (double)WIDTH*(WIDTH);
    return ox;
}

float getOpenGLY(int y)
{
    double oy = (1 - y/ (double) HEIGHT)*HEIGHT;
    return oy;
}

void drawPoints()
{
    glBegin( GL_POINTS );
    glColor3f( 0.0,1.0,0.0 );
    for ( int i = 0; i < z; i++ )
    {
        glVertex2f( arr[i][0],arr[i][1]);
    }
    glEnd();
}

void drawBall(float x,float y)
{
    glBegin( GL_POINTS);
    glColor3f( 1.0,1.0,0.0 );
    glVertex2f(x,y);
    glEnd();
}

void drawLines()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,0.0,0.0);
    for(int i=0;i<z;i++)
    {
        glVertex2f(arr[i][0],arr[i][1]);
    }
    glEnd();
}


void addValue(int x,int y)
{
    arr[z][0]=getOpenGLX(x);
    arr[z++][1]=getOpenGLY(y);
}

void trackBall()
{
    drawPoints();
}


void myDisplay()
{
    glClear( GL_COLOR_BUFFER_BIT);
    if(!flag)
    {
        drawLines();
        drawBall(arr[ptr][0],arr[ptr][1]);
    }
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}


void myMouseStat(int button,int state,int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(!flag)
        {
            resetAll();
            flag=1;
        }
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if(flag)
        {
            ptr=0;
            flag=0;
        }
    }
}


void myPressedMove(int x,int y)
{
    if(flag)
    {
        addValue(x,y);
    }
}



void myTimer(int t)
{
    if(ptr!=z)
    {
         ptr++;
    }
    else
{
    ptr=0;
}
    glutTimerFunc(100,myTimer,0);
}

int main( int argc, char ** argv)
{
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow( "Testing");
    init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouseStat);
    glutMotionFunc(myPressedMove);
    glutTimerFunc(100,myTimer,0);
    glutMainLoop();
    return 0;
}
