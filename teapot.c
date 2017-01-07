#include <GL/glut.h>

void obj(double tx,double ty,double tz,double sx,double sy,double sz)
{
    glRotated(50,0,1,0);
    glRotated(10,-1,0,0);
    glRotated(11.7,0,0,-1);

    glTranslated(tx,ty,tz);
    glScaled(sx,sy,sz);
    glutSolidCube(1);
    glLoadIdentity();
}

void display()
{
    glViewport(0,0,700,700);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    obj(0,0,0.5,1,1,0.04);
    obj(0,-0.5,0,1,0.04,1);
    obj(-0.5,0,0,0.04,1,1);
    
    obj(0,-0.3,0,0.02,0.2,0.02);
    obj(0,-0.3,-0.4,0.02,0.2,0.02);
    obj(0.4,-0.3,0,0.02,0.2,0.02);
    obj(0.4,-0.3,-0.4,0.02,0.2,0.02);

    obj(0.2,-0.18,-0.2,0.6,0.02,0.6);

    glRotated(50,0,1,0);
    glRotated(10,-1,0,0);
    glRotated(11.7,0,0,-1);

    glTranslated(0.3,-0.1,-0.3);

    glutSolidTeapot(0.1);
    glFlush();
    glLoadIdentity();
}

int main(int argc,char** argv)
{
    float ambient[]={0.7,0.7,0.7,0.7};
    float lightpos[] = {27,80,2,3};
    float shine[]={50.0};
    glutInit(&argc,argv);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("TeaPot");
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
   // glMaterialfv(GL_FRONT,GL_SHININESS,shine);
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();


}