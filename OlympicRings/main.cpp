#include <gl/glut.h>
#include <math.h>

const GLfloat screenWidth = 800,screenHeight = 800;
const GLfloat colors[5][3]={{0.0,0.0,1.0},{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0}};

int yc[2]={500,400};
int xc[2]={200,305};
int r=100;

void putPixel(int x, int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void doSimetria(int x,int y,int xc,int yc)  //Oba metoda koriste simetriju!
{
	putPixel(x+xc,y+yc);
	putPixel(-x+xc,y+yc);
	putPixel(-y+xc,x+yc);
	putPixel(-y+xc,-x+yc);
    putPixel(-x+xc,-y+yc);
	putPixel(x+xc,-y+yc);
    putPixel(y+xc,-x+yc);
	putPixel(y+xc,x+yc);
}

void rasterize(int xc,int yc,int r,int mode) //0->B, 1->midpoint
{
	int x=0,y=r,p;
	if(mode==0)
		p=3-2*r;
	else
		p=1-r;
	doSimetria(x,y,xc,yc);
	while(y>x)
	{
		if(p>=0)
		{
			if(mode==0)
				p=p+4*(x-y)+6;
			else
				p=p+2*(x-y)+5;
			y--;
		}
		else
			{
				if(mode==0)
					p=p+4*x+6;
				else
					p=p+2*x+3;
		}
		doSimetria(x,y,xc,yc);
		x++;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i=0,j=0;i<5;i++)
	{
		glColor3fv(colors[i]);
		rasterize(xc[j],yc[j],r,0); //promjena metoda rasterizacije
		xc[j]=xc[j]+2*r+10;
		if(i==2)
			j++;
	}
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("OlympicRings");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}