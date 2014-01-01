#include <iostream>
#include <glut.h>
#include <math.h>
#include <stdio.h>

//Width and Heigth of the image
double WIDTH  = 500;
double HEIGHT = 500;

typedef struct Point
{
	double x;
	double y;
} Point;

typedef struct Vector
{
	double x;
	double y;
} Vector;

Point arr[5000];
Point arrWin[4] = {{0,0},{0,500},{500,500},{500,0}};
//stocke les normales de la fenêtre
Vector arrNormale[4];
//stocke le polygone découpé
Vector cutedPolygon[5000];
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

double max(double a, double b)
{
	if (a > b)
		return a;
	else
		return b;
}

double min(double a, double b)
{
	if (a < b)
		return a;
	else
		return b;
}

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
        glVertex2f( arr[i].x, arr[i].y);
    }
    glEnd();
}

void drawRect()
{
    glColor3ub(0,0,255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(arrWin[0].x,arrWin[0].y);
    glVertex2i(arrWin[1].x,arrWin[1].y);
    glVertex2i(arrWin[2].x,arrWin[2].y);
    glVertex2i(arrWin[3].x,arrWin[3].y);
    glEnd();
}

void drawPoly()
{
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
    for(int i=0;i<z;i++)
    {
        glVertex2i(arr[i].x,arr[i].y);
    }
    glEnd();
}

//Affiche la vue de la fenêtre précisée dans Testing
void displayView()
{

}

void addValue(int x,int y)
{
    arr[z].x=getOpenGLX(x);
    arr[z++].y=getOpenGLY(y);
}

void addWinValue(int x,int y)
{
    if(z2 == 0){
        arrWin[0].x=getOpenGLX(x);
        arrWin[0].y=getOpenGLY(y);
        z2 = 1;
    }
    else if(z2 == 1){
        arrWin[1].x=getOpenGLX(x);
        arrWin[1].y=getOpenGLY(y);
        z2 = 2;
    }
    else if(z2 == 2){
        arrWin[2].x=getOpenGLX(x);
        arrWin[2].y=getOpenGLY(y);
        z2 = 3;
    }
    else if(z2 == 3){
        arrWin[3].x=getOpenGLX(x);
        arrWin[3].y=getOpenGLY(y);
        z2 = 0;
    }
}


void myDisplay()
{
     glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, WIDTH, -2, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );
    drawPoly();
    drawRect();
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

void reshape(GLsizei w, GLsizei h) {
    WIDTH=w; HEIGHT=h;
    glViewport(0,0,WIDTH,HEIGHT);
    glutPostRedisplay();
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

//CyrusBeck
bool CyrusBeck(double x1, double x2, double y1, double y2, int nbSom, Point poly[5000], Vector arrNormale[4])
{
	double t, tInf, tSup;
	double dx, dy, wn, dn;
	Point current;
	int i, nbSeg;

	tInf = -5000;
	tSup = 5000;
	dx = x2 - x1;
	dy = y2 - y1;
	nbSeg = nbSom - 1;

	for (i = 1; i = nbSeg; i++)
	{
		current = poly[i];

		dn = dx * arrNormale[i].x + dy * arrNormale[i].y;
		wn = (x1 - current.x) * arrNormale[i].x + (y1 - current.y) * arrNormale[i].y;

		if(dn = 0)
			return wn >= 0;
		else
		{
			t = -wn/dn;
			if (dn > 0)
			{
				if(t > tInf)
					tInf = t;
			}
			else
			{
				if(t < tSup)
					tSup = t;
			}
		}
	}

	if (tInf<tSup)
	{
		if (tInf < 0 && tSup > 1)
			return true;
		else
		{
			if (tInf>1 || tSup <0)
				return false;
			else
			{
				if(tSup > 1)
					tSup = 1;
			}
			x2 = x1 + dx * tSup;
			y2 = y1 + dy * tSup;
			x1 = x1 + dx * tSup;
			y1 = y1 + dx * tInf;
			return true;
		}
	}
	else
		return false;
}

Vector normale(Point p1, Point p2)
{
	Vector v;
	v.y = p2.x - p1.x;
	v.x = - p2.y - p1.x;
	return v;
}

void updateNormale(Point poly[4])
{
	for(int i = 0; i <5000; i++)
	{
		arrNormale[i] = normale(poly[i], poly[i+1]);
	}
}


bool visible(Point S, Point F1, Point F2)
{
	Vector n = normale(F1, F2);
	Vector k ;
	k.x = S.x-F1.x;
	k.y = S.y-F1.y;

	if (n.x*k.x + n.y * k.y >= 0)
		return true;		// à droite
	else
		return false;		//Si sur le segment = visible
}

bool coupe(Point S, Point P, Point F1, Point F2)
{
	double a1, a2, b1, b2, y, x;
	a1 = (F1.y-F2.y)/(F2.y-F1.y);
	b1 = F2.y - a1 * F2.x;
	a2 = (P.y-S.y)/(P.y-S.y);
	b2 = P.y - a1 * P.x;
	x = (b2 - b1)/(a1 - a2);
	y = a1 * x + b1;

	if(x <= max(S.x, P.x) && x >= min(S.x, P.x) && y <= max(S.y, P.y) && y>= min(S.y, P.y))
		return true;
	else
		return false;
}

Point intersection(Point S, Point P, Point F1, Point F2)
{
	double a1, a2, b1, b2, y, x;
	a1 = (F1.y-F2.y)/(F2.y-F1.y);
	b1 = F2.y - a1 * F2.x;
	a2 = (P.y-S.y)/(P.y-S.y);
	b2 = P.y - a1 * P.x;
	x = (b2 - b1)/(a1 - a2);
	y = a1 * x + b1;
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

//Sutherland-Hodgman
void decoupage(Point PL[5000], Point PW[4])
{
    int n1 = z -1;
    int n3 = 4;
	int i, j, n2;
	Point current, F, I;

    printf("\ntest");

	for (i = 0; i = n3-1; i++)
	{
	    printf("\ntest1");
		n2 = 0;
		for ( j=0; j = n1; j++)
		{
			if (j = 1)
				F = PL[j];
			else
			{
				if( coupe(current, PL[j], PW[i], PW[i+1]))
				{
					I = intersection(current, PL[j], PW[i], PW[i+1]);
					cutedPolygon[n2].x = I.x;
					cutedPolygon[n2].y = I.y;
					n2++;
				}
			}
			current = PW[j];
			if(visible(current, PW[i], PW[i+1]))
			{
				cutedPolygon[n2].x = current.x;
				cutedPolygon[n2].y = current.y;
				n2++;
			}
		}
		if (n2>0)
		{
			if( coupe(current, F, PW[i], PW[i+1]))
			{

			}
            int temp = 0;
            for(temp; temp < 5000; temp++)
            {
             PL[temp].x = cutedPolygon[temp].x;
             PL[temp].y = cutedPolygon[temp].y;
            }
			n1 = n2;
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
            decoupage(arr, arrWin);
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
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glutCreateMenu(menu);
    glutMainLoop();
    return 0;
}
