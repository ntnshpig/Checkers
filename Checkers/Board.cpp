#include "Board.h"
#include "glut.h"
void Board::draw_Box() {
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.3f, 0.0f);
    glVertex3f(1.50f, 0.3f, 0.0f);
    glVertex3f(1.5f, 0.3f, -1.5f);
    glVertex3f(0.0f, 0.3f, -1.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.05f);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.50f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.3f, 0.0f);
    glVertex3f(0.0f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glVertex3f(0.0f, 0.3f, -1.5f);
    glVertex3f(0.0f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.5f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.0f, -1.5f);
    glVertex3f(1.5f, 0.3f, -1.5f);
    glVertex3f(1.5f, 0.3f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glVertex3f(1.50f, 0.0f, -1.5f);
    glVertex3f(1.5f, 0.3f, -1.5f);
    glVertex3f(0.0f, 0.3f, -1.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.50f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.0f, -1.5f);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glEnd();
}