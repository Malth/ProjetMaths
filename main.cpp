#include <iostream>
#include <glut.h>


double WIDTH  = 500;
double HEIGHT = 500;

double arr[5000][2];
double arrWin[2][2] = {{0,0},{500,500}};
int z=0;
int z2=0;
int flag2=0;
int fmen = 0;
float radius=0.03;
float color[3][3]={{1.0,1.0,1.0},{1.0,1.0,0.0},{0.0,1.0,0.0}};

enum MENU_TYPE
{
        MENU_POL,
        MENU_WIN,
        MENU_APP,
        MENU_BACK,
        MENU_BACK_FRONT,
};

MENU_TYPE show = MENU_BACK_FRONT;

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
    double ox = x/ (double)WIDTH*WIDTH;
    return ox;
}

float getOpenGLY(int y)
{
    double oy = (1-y/ (double) HEIGHT)*HEIGHT;
    return oy;
}

void drawPoints()
{
    glBegin( GL_POINTS );
    for ( int i = 0; i < z; i++ )
    {
        glVertex2f( arr[i][0], arr[i][1]);
    }
    glEnd();
}

void drawRect()
{
    glColor3ub(0,0,255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(arrWin[0][0],arrWin[0][1]);
    glVertex2i(arrWin[1][0],arrWin[0][1]);
    glVertex2i(arrWin[1][0],arrWin[1][1]);
    glVertex2i(arrWin[0][0],arrWin[1][1]);
    glEnd();
}

void drawPoly()
{
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
    for(int i=0;i<z;i++)
    {
        glVertex2i(arr[i][0],arr[i][1]);
    }
    glEnd();
}

void addValue(int x,int y)
{
    arr[z][0]=getOpenGLX(x);
    arr[z++][1]=getOpenGLY(y);
}

void addWinValue(int x,int y)
{
    if(z2 == 0){
        arrWin[0][0]=getOpenGLX(x);
        arrWin[0][1]=getOpenGLY(y);
        z2 = 1;
    }
    else if(z2 == 1){
        arrWin[1][0]=getOpenGLX(x);
        arrWin[1][1]=getOpenGLY(y);
        z2 = 0;
    }
}


void myDisplay()
{
    glClear( GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    drawPoly();
    drawRect();
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

void reshape (int w, int h)
{
    glViewport(0,0,w,h);
  	//gluPerspective(45,float(WIDTH)/float(HEIGHT),10,100);
}


void myMouseStat(int button,int state,int x, int y)
{
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        //Right Click
    }
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        if(fmen == 0){
            addValue(x,y);
        }
        else if(fmen == 1){
            addWinValue(x,y);
        }
    }

}

void menu(int item)
{
        switch (item)
        {
        case MENU_POL:
            fmen = 0;
            break;
        case MENU_WIN:
            fmen = 1;
            break;
        case MENU_BACK:
            resetAll();
            break;
        case MENU_APP:
            fmen = 3;
            break;
        case MENU_BACK_FRONT:
            show = (MENU_TYPE) item;
            break;
        default:
            break;
        }

        glutPostRedisplay();

        return;
}

void clavier(unsigned char touche,int x,int y){
	switch (touche){

		case 'p':
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glutPostRedisplay();
			break;

		case 'f':
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glutPostRedisplay();
			break;

		case 's':
			glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
			glutPostRedisplay();
			break;

		case 'q':
			exit(0);
	}
}

int main( int argc, char ** argv)
{
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow( "Testing");
    init();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouseStat);
    glutKeyboardFunc(clavier);
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3ub(255,0,0);

    glutCreateMenu(menu);
    glutAddMenuEntry("Change To Polygon", MENU_POL);
    glutAddMenuEntry("Change To Window", MENU_WIN);
    glutAddMenuEntry("Survey", MENU_APP);
    glutAddMenuEntry("Reset", MENU_BACK);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
