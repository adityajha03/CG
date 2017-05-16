/*Cylinder */
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void draw_pixel(GLint cx,GLint cy)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(cx,cy);
	glEnd();
}
void plotpixel(GLint h,GLint k,GLint x,GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
}
void text(float x, float y, char *s)
{
int i;
glRasterPos2f(x,y);
for(i=0;s[i]!='\0';i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
}

//Midpoint circle drawing algo
void circle_draw(GLint h,GLint k,GLint r)
{
 GLint d = 1-r,x=0,y=r;
 while(y>x)
 {
 	plotpixel(h,k,x,y);
 	if(d<0)
 	  d+=2*x+3;
 	else
 	{
 	 d+=2*(x-y)+5;
 	 --y;
 	}
   ++x;
 }
plotpixel(h,k,x,y);
}
void cylinder_draw()
{
 GLint xc=100,yc=100,r=50;
 GLint i,n=50;
 for(i-0;i<n;i+=3)
 {
  circle_draw(xc,yc+i,r);
 }
}
void parallelopiped(int x1,int x2,int y1,int y2,int y3,int y4)
{
	glColor3f(0.0,0.0,1.0);
	glPointSize(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1,y1);
	glVertex2i(x2,y3);
	glVertex2i(x2,y4);
	glVertex2i(x1,y2);
	glEnd();
}
void parallelopiped_draw()
{
	int x1=200,x2=300,y1=100,y2=175,y3=100,y4=175;
	GLint i,n=40;
	for(i=0;i<n;i+=2)
	{
	 parallelopiped(x1+i,x2+i,y1+i,y2+i,y3+i,y4+i);
	}
}
void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
 	glColor3f(1.0,0.0,0.0);
	glPointSize(2.0);
	cylinder_draw();
	parallelopiped_draw();
	text(25,365,"Harsh Rana");
	text(25,345,"1BI14CS212");
	text(25,325,"Cylinder & parallelopiped display");
	glFlush();
}
void main(int argc,char **argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(400,300);
 glutInitWindowPosition(50,50);
 glutCreateWindow("Cylinder & Parallelopiped Display ");
 glutDisplayFunc(display);
 init();
 glutMainLoop();
}

	













