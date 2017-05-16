#include<stdio.h>
#include<GL/glut.h>
#include<stdbool.h>
double xmin=50, ymin=50, xmax=100, ymax=100;
double xvmin=200, yvmin=200, xvmax=300, yvmax=300;
double x[50], y[50];
int n;
int cliptest(double p, double q, double *t1, double *t2)
{
	double t=q/p;
	if(p<0.0)
	{
		if(t>*t1)  *t1=t;
		if(t>*t2)  return(false);
	}
	else
	if(p>0.0)
	{
		if(t<*t2)  *t2=t;
		if(t<*t1)  return(false);
	}
	else
	if(p==0.0)
	{
		if(q<0.0) return(false);
	}
	return(true);
}

void liang(double x0,double y0,double x1,double y1)
{
	double dx=x1-x0, dy=y1-y0,te=0.0,tl=1.0;
	if(cliptest(-dx,x0-xmin,&te,&tl))	
	if(cliptest(dx,xmax-x0,&te,&tl))
	if(cliptest(-dy,y0-ymin,&te,&tl))
	if(cliptest(dy,ymax-y0,&te,&tl))
	{
		if(tl<1.0)
		{
			x1=x0+tl*dx;
			y1=y0+tl*dy;
		}
		if(te>0.0)
		{
			x0=x0+te*dx;
			y0=y0+te*dy;
		}
		double sx=(xvmax-xvmin)/(xmax-xmin);
		double  sy=(yvmax-yvmin)/(ymax-ymin);
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
	       glVertex2f(vx0,vy0);
	       glVertex2f(vx1,vy1);
	       glEnd();
	       
       }
}

void text(float x, float y, char *s)
{
int i;
glRasterPos2f(x,y);
for(i=0;s[i]!='\0';i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
}


void display()
{
int i;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINES);
for(i=0;i<n;i++)
{
	glVertex2f(x[2*i],y[2*i]);
	glVertex2f(x[2*i+1],y[2*i+1]);
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
liang(x[2*i],y[2*i],x[2*i+1],y[2*i+1]);
text(25,365,"BHAVISH");
text(25,345,"1BI14CS041");
text(25,325,"Liang Barsky Line Clipping Algorithm");
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
     glMatrixMode(GL_MODELVIEW);
   }
   
  void main(int argc,char **argv)
 {
 int i;
 printf("Enter the number of lines\n");
 scanf("%d",&n);
 printf("Enter the x and y coordinates of the line segments\n");
 for(i=0;i<(2*n);i++)
 scanf("%lf %lf",&x[i],&y[i]);
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
     glutInitWindowSize(500,500);
     glutInitWindowPosition(0,0);
     glutCreateWindow("Liang Barsky Line Clipping Algorithm");
     glutDisplayFunc(display);
     myinit();
     glutMainLoop();
     }   
	
