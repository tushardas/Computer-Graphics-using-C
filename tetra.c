#include<GL/glut.h>
GLint n;
GLfloat ver[][3] = {{0.0,0.0,1.0},{0.0,2.0,-1.0},{-2.0,-2.0,-1.0},{2.0,-2.0,-1.0}};

void triangle(GLfloat *va,GLfloat *vb,GLfloat *vc)
{
    glVertex3fv(va);
    glVertex3fv(vb);
    glVertex3fv(vc);
}

void tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
    glColor3f(1.0,0.0,0.0);
    triangle(a,b,c);

    glColor3f(0.0,1.0,0.0);
    triangle(a,c,d);

    glColor3f(0.0,0.0,1.0);
    triangle(a,d,b);

    glColor3f(1.0,0.0,1.0);
    triangle(b,d,c);
}

void divide(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,GLint m)
{
    GLfloat mid[6][3];
    GLint i,j;

    if(m > 0)
    {
        for(j=0;j<3;j++)    mid[0][j] = (a[j]+b[j])/2;
        for(j=0;j<3;j++)    mid[1][j] = (a[j]+c[j])/2;
        for(j=0;j<3;j++)    mid[2][j] = (a[j]+d[j])/2;
        for(j=0;j<3;j++)    mid[3][j] = (d[j]+b[j])/2;
        for(j=0;j<3;j++)    mid[4][j] = (c[j]+d[j])/2;
        for(j=0;j<3;j++)    mid[5][j] = (c[j]+b[j])/2;

        divide(a,mid[0],mid[1],mid[2],m-1);
        divide(mid[0],b,mid[3],mid[5],m-1);
        divide(mid[1],mid[4],c,mid[5],m-1);
        divide(mid[2],mid[3],mid[4],d,m-1);
    }

    else    tetra(a,b,c,d);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    glBegin(GL_TRIANGLES);
    divide(ver[0],ver[1],ver[2],ver[3],n);
    glEnd();
    glFlush();
}

void init()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0,5.0,-5.0,5.0,-5.0,5.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc,char **argv)
{
    n =atoi(argv[1]);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_DEPTH|GLUT_RGB);
    glutCreateWindow("3D Gasket");
    glutDisplayFunc(display);
    init();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    glutMainLoop();
}
