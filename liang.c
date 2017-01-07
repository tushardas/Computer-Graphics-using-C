#include <GL/glut.h>
#include <stdio.h>

double x0, y0, x1, y1, xmax, ymax, xmin, ymin, xvmax, yvmax, xvmin, yvmin;

int cliptest(double p, double q, double *t1, double *t2)
{
    double t = q / p;

    if (p < 0.0)
    {
        if (t > *t1)
            *t1 = t;
        if (t > *t2)
            return 0;
    }

    else if (p > 0.0)
    {
        if (t < *t2)
            *t2 = t;
        if (t < *t1)
            return 0;
    }

    else if (p == 0.0)
    {
        if (q < 0.0)
            return 0;
    }

    return 1;
}

void liangclipanddraw(double x0, double y0, double x1, double y1)
{
    double dx = x1 - x0, dy = y1 - y0, te = 0.0, t1 = 1.0;
    double sx, sy, vx0, vy0, vx1, vy1;

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(xvmin, yvmin);
    glVertex2d(xvmin, yvmax);
    glVertex2d(xvmax, yvmax);
    glVertex2d(xvmax, yvmin);
    glEnd();

    if (cliptest(-dx, x0 - xmin, &te, &t1))
        if (cliptest(dx, xmax - x0, &te, &t1))
            if (cliptest(-dy, y0 - ymin, &te, &t1))
                if (cliptest(dy, ymax - y0, &te, &t1))
                {
                    if (t1 < 1.0)
                    {
                        x1 = x0 + t1 * dx;
                        y1 = y0 + t1 * dy;
                    }

                    if (te > 0.0)
                    {
                        x0 = x0 + te * dx;
                        y0 = y0 + te * dy;
                    }

                    sx = (xvmax - xvmin) / (xmax - xmin);
                    sy = (yvmax - yvmin) / (ymax - ymin);

                    vx0 = xvmin + (x0 - xmin) * sx;
                    vy0 = yvmin + (y0 - ymin) * sy;
                    vx1 = xvmin + (x1 - xmin) * sx;
                    vy1 = yvmin + (y1 - ymin) * sy;

                    glColor3f(1.0, 1.0, 1.0);
                    glBegin(GL_LINES);
                    glVertex2f(vx0, vy0);
                    glVertex2f(vx1, vy1);
                    glEnd();
                }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmin, ymax);
    glVertex2d(xmax, ymax);
    glVertex2d(xmax, ymin);
    glEnd();

    liangclipanddraw(x0, y0, x1, y1);

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    printf("\nEnter starting point: ");
    scanf("%lf %lf", &x0, &y0);
    printf("\nEnter ending point: ");
    scanf("%lf %lf", &x1, &y1);

    printf("\nEnter lower part of window: ");
    scanf("%lf %lf", &xmin, &ymin);

    printf("\nEnter upper part of window: ");
    scanf("%lf %lf", &xmax, &ymax);

    printf("\nEnter lower part of ViewPort: ");
    scanf("%lf %lf", &xvmin, &yvmin);

    printf("\nEnter upper part of ViewPort: ");
    scanf("%lf %lf", &xvmax, &yvmax);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Liang Barsky");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
