#include <GL/glut.h>

void init()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,500.0);
    glMatrixMode(GL_MODELVIEW);

}

void drawp(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
    glBegin(GL_LINE_LOOP);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glVertex2i(x3,y3);
        glVertex2i(x4,y4);
    glEnd();
}

void parallel()
{
    int x1 = 300, y1 =200;
    int x2 = 300, y2 = 300;
    int x3 = 400, y3 = 300;
    int x4 = 400, y4 = 200;

    for(int i=0;i<50;i+=3)
    {
        drawp(x1+i,y1+i,x2+i,y2+i,x3+i,y3+i,x4+i,y4+i);
    }

}

void drawpixel(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void plot(int h,int k,int x,int y)
{
    drawpixel(x+h,y+k);
    drawpixel(-x+h,y+k);
    drawpixel(-x+h,-y+k);
    drawpixel(x+h,-y+k);

    drawpixel(y+h,x+k);
    drawpixel(-y+h,x+k);
    drawpixel(-y+h,-x+k);
    drawpixel(y+h,-x+k);
    

}

void drawc(int h,int k,int r)
{
    int d = 1-r , x=0,y=r;

    while(y>x)
    {
        plot(h,k,x,y);

        if(d<0)
            d += 2*x+3;
        else
        {
            d += 2*(x-y)+5;
            --y;
        }

        ++x;
    }

    plot(h,k,x,y);

}
void circledraw()
{
    int xc = 100,yc =100, r=30;

    for(int i=0;i<50;i+=3)
        drawc(xc,yc+i,r);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,0.0,0.0);
    parallel();

    glColor3f(0.0,0.0,1.0);
    circledraw();

    glFlush();
}


int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Parallelepiped and Cylinder");
    glutDisplayFunc(display);
    init();
    glutMainLoop();

}