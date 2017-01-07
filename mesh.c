#include <GL/glut.h>

#define maxx 10
#define maxy 15
#define dx 15
#define dy 10

GLfloat x[maxx], y[maxy];
GLint x0=50,yq=50;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i=0;i<maxx;i++)
        x[i] = x0 + i*dx;


    for (int j=0;j<maxy;j++)
        y[j] = yq + j*dy;

    for(int i=0;i<maxx-1;i++)
    for(int j=0;j<maxy-1;j++)
    {
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINE_LOOP);

        glVertex2f(x[i],y[j]);
        glVertex2f(x[i],y[j+1]);
        glVertex2f(x[i+1],y[j+1]);
        glVertex2f(x[i+1],y[j]);

        glEnd();

    }

    glFlush();
}


void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(0,1000);

    glutCreateWindow("Mesh");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
