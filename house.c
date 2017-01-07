#include <GL/glut.h>
#include <stdio.h>
GLfloat theta,inc;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(theta,0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(0,0);
        glVertex2i(100,0);
        glVertex2i(100,100);
        glVertex2i(0,100);
    glEnd();

     glBegin(GL_LINE_LOOP);
        glVertex2i(25,0);
        glVertex2i(25,30);
        glVertex2i(75,30);
        glVertex2i(75,0);
    glEnd();

     glBegin(GL_LINE_LOOP);
        glVertex2i(0,100);
        glVertex2i(100,100);
        glVertex2i(50,150);
     glEnd();
     glFlush();
}


void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200,200,-200,200);
    glMatrixMode(GL_MODELVIEW);
}


void rot()
{
    theta += inc;
    glutPostRedisplay();
}

int main(int argc,char **argv)
{
    printf("Enter theta and inc: ");
    scanf("%f %f", &theta,&inc);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("House");
    glutDisplayFunc(display);
    glutIdleFunc(rot);
    init();
    glutMainLoop();
}

