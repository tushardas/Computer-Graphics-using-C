#include <GL/glut.h>
#include <stdio.h>
#define outcode int
double x0,y0,x1,y1;
double xmin,ymin,xmax,ymax;
double xvmin,yvmin,xvmax,yvmax;
 const int TOP = 8;
 const int BOTTOM = 4;
 const int RIGHT = 2;
 const int LEFT = 1;

outcode computecod(double x,double y)
{
    outcode code =0;

    if(y>ymax)
        code |= TOP;
    
    if(y<ymin)
        code |= BOTTOM;
    
    if(x>xmax)
        code |= RIGHT;

    if(x<xmin)
        code |= LEFT;
    
    return code;

}
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,500.0);
    glMatrixMode(GL_MODELVIEW);
}

void cohenclipanddraw(double x0,double y0,double x1,double y1)
{
    double sx,sy,vx0,vy0,vx1,vy1;
    int accept =0,done=0;
    outcode outcode0,outcode1,outcodeout;

   
    outcode0 = computecod(x0,y0);
    outcode1 = computecod(x1,y1);

    do{

    
    if(!(outcode0 | outcode1))
    {
        accept = 1;
        done = 1;
    }

    else if(outcode0 & outcode1)
        done = 1;

    else
    {
        double x,y;

        outcodeout = outcode0?outcode0:outcode1;

        if(outcodeout & TOP)
        {
            x = x0+(x1-x0)*(ymax-y0)/(y1-y0);
            y = ymax;
        }

        else if(outcodeout & BOTTOM)
        {
            x = x0+(x1-x0)*(ymin-y0)/(y1-y0);
            y = ymin;
        }

        else if(outcodeout & RIGHT)
        {
            y = y0+ (y1-y0)*(xmax-x0)/(x1-x0);
            x = xmax;
        }

        else if(outcodeout & LEFT)
        {
            y = y0+ (y1-y0)*(xmin-x0)/(x1-x0);
            x = xmin;
        }

        if(outcodeout == outcode0)
        {
            x0=x;
            y0=y;
            outcode0 = computecod(x0,y0);
        }

        else
        {
            x1 = x;
            y1 = y;
            outcode1 = computecod(x1,y1);
        }


    }

    }while(!done);

     glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmin,yvmax);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmax,yvmin);
    glEnd();


    if(accept)
    {
        sx = (xvmax-xvmin)/(xmax-xmin);
        sy = (yvmax-yvmin)/(ymax-ymin);

        vx0 = xvmin + (x0-xmin)*sx;
        vy0 = yvmin + (y0-ymin)*sy;
        vx1 = xvmin + (x1-xmin)*sx;
        vy1 = yvmin + (y1-ymin)*sy;

        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINES);
            glVertex2f(vx0,vy0);
            glVertex2f(vx1,vy1);
        glEnd();

        

    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2f(x0,y0);
        glVertex2f(x1,y1);
    glEnd();


    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
    glEnd();

    cohenclipanddraw(x0,y0,x1,y1);

    glFlush();
}

int main(int argc, char** argv)
{
    printf("Enter the initial point: ");
    scanf("%lf %lf",&x0,&y0);

    printf("Enter the final point: ");
    scanf("%lf %lf",&x1,&y1);

    printf("Enter the window lower point: ");
    scanf("%lf %lf",&xmin,&ymin);

    printf("Enter the window upper point: ");
    scanf("%lf %lf",&xmax,&ymax);

    printf("Enter the viewport lower point: ");
    scanf("%lf %lf",&xvmin,&yvmin);

    printf("Enter the viewport upper point: ");
    scanf("%lf %lf",&xvmax,&yvmax);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Cohen Sutherland");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}