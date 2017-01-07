#include<GL/glut.h>
#include<stdlib.h>
//                    0                1               2              3             4                5               6              7
GLfloat v[][3] = {{-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},{-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0}};

GLfloat col[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,-1.0},{1.0,1.0,-1.0}};


GLfloat theta[] = {0.0,0.0,0.0};
GLint axis = 2;
void polygon(int a,int b,int c,int d)
{

    glBegin(GL_POLYGON);
        glVertex3fv(v[a]);
        glVertex3fv(v[b]);
        glVertex3fv(v[c]);
        glVertex3fv(v[d]);
    glEnd();
}

void cube()
{
    glColor3f(1.0,0.0,0.0);
    polygon(0,3,2,1);
    glColor3f(1.0,1.0,1.0);
    polygon(2,6,5,1);
    glColor3f(0.0,1.0,0.0);
    polygon(6,2,3,7);
    glColor3f(0.0,0.0,1.0);
    polygon(4,5,6,7);
    glColor3f(1.0,1.0,0.0);
    polygon(3,0,4,7);
    glColor3f(1.0,0.0,1.0);
    polygon(1,5,4,0);

}
int n;
void spin()
{

    theta[axis] += n;
    if (theta[axis] >= 360.0) theta[axis] -= 360.0;

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cube();
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    
    glFlush();
    glutSwapBuffers();

}

void init()
{
    glClearColor(0.5,0.5,0.5,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn,int state,int x,int y)
{
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis =0;
    if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis =1;
    if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis =2;
}

int main(int argc,char **argv)
{
    n = atoi(argv[1]);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("Cube");
    glutDisplayFunc(display);
    glutIdleFunc(spin);
    glutMouseFunc(mouse);
    init();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
