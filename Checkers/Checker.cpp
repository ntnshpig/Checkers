#include "Checker.h"
#include "glut.h"
#include <cmath>
void Checker::draw_Cylinder() {
    const double PI = 3.14159;

    /* Верхнє коло */
    double i, resolution = 0.1;
    double height = 0.4;
    double radius = 0.5;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, height, 0);  /* Центер */
    for (i = 2 * PI; i >= 0; i -= resolution)

    {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    glTexCoord2f(0.5, 0.5);
    glVertex3f(radius, height, 0);
    glEnd();

    /*Нижнє коло(у зворотньому порядку) */
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 0, 0);  /* Центер */
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
    }
    glEnd();

    /* Середина конуса */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        const float tc = (i / (float)(2 * PI));
        glTexCoord2f(tc, 0.0);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
        glTexCoord2f(tc, 1.0);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    glTexCoord2f(0.0, 0.0);
    glVertex3f(radius, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();
}
void Checker::draw_Queen() {
    glBegin(GL_TRIANGLES);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    glBegin(GL_QUADS);// основание пирамиды

    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();
}