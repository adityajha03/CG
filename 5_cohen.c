#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include<stdio.h>
#include<stdbool.h>
double xmin=100,ymin=100,xmax=150,ymax=150;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;
const int TOP=8;
const int BOTTOM=4;
const int RIGHT=2;
const int LEFT=1;
double x[50],y[50];
int n;
int ComputeOutCode(double x,double y);
void draw_text(float x,float y,char *s)
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;s[i]!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);
}
void CohenSutherlandLineClipAndDraw(double x0,double y0,double x1,double y1)
{
	int outcode0,outcode1,outcodeOut;
	bool accept=false,done=false;
	outcode0=ComputeOutCode(x0,y0);
	outcode1=ComputeOutCode(x1,y1);
	do{
		if((outcode0|outcode1)==0)
		{
			accept=true;
			done=true;
		}
		else if(outcode0 & outcode1)
		done=true;
		else
		{
			double x,y;
			outcodeOut=outcode0 ? outcode0 : outcode1;
			float slope=(y1-y0)/(x1-x0);
			if(outcodeOut & TOP)
			{
				x=x0+(1/slope)*(ymax-y0);
				y=ymax;
			}
			else if(outcodeOut & BOTTOM)
			{
				x=x0+(1/slope)*(ymin-y0);
				y=ymin;
			}
			else if(outcodeOut & RIGHT)
			{
				y=y0+slope*(xmax-x0);
				x=xmax;
			}
			else
			{
				y=y0+slope*(xmin-x0);
				x=xmin;
			}
			if(outcodeOut==outcode0)
			{
				x0=x;
				y0=y;
				outcode0=ComputeOutCode(x0,y0);
			}
			else
			{
				x1=x;
				y1=y;
				outcode1=ComputeOutCode(x1,y1);
			}
		}
	}
	while(!done);
	if(accept)
	{
		double sx=(xvmax-xvmin)/(xmax-xmin);
		double sy=(yvmax-yvmin)/(ymax-ymin);
		double vx0=xvmin+(x0-xmin)*sx;
		double vy0=yvmin+(y0-ymin)*sy;
		double vx1=xvmin+(x1-xmin)*sx;
		double vy1=yvmin+(y1-ymin)*sy;
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin,yvmin);
		glVertex2f(xvmax,yvmin);
		glVertex2f(xvmax,yvmax);
		glVertex2f(xvmin,yvmax);
		glEnd();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex2d(vx0,vy0);
		glVertex2d(vx1,vy1);
		glEnd();
	}
}
int ComputeOutCode(double x,double y)
{
	int code=0;
	if(y>ymax)
	code|=TOP;
	else if(y<ymin)
	code|=BOTTOM;
	if(x>xmax)
	code|=RIGHT;
	else if(x<xmin)
	code|=LEFT;
	return code;
}
void display()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	for(i=0;i<n;i++)
	{
		glVertex2d(x[2*i],y[2*i]);
		glVertex2d(x[(2*i)+1],y[(2*i)+1]);
	}
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
	for(i=0;i<n;i++)
	{
		CohenSutherlandLineClipAndDraw(x[2*i],y[2*i],x[2*i+1],y[2*i+1]);
	}
	draw_text(350,400,"Aditya Kumar Jha");
	draw_text(350,385,"1BI14CS005");
	glFlush();
}
void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void main(int argc,char **argv)
{
	int i;
	printf("Enter the no. of lines:");
	scanf("%d",&n);
	printf("Enter the x and y co-ordinates of the line segments\n");
	for(i=0;i<(2*n);i++)
		scanf("%lf %lf",&x[i],&y[i]);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cohem Sutherland Line Clipping Algorithm");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
