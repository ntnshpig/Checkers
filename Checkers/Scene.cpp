#include "Scene.h"
#include "glut.h"
#include "Board.h"
#include "Checker.h"
#include "Game.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
bool Scene::findNearest(int x, int y, int& x1, int& z1) {
    float i = 0.0;
    float j = 0.0;
    int viewport[4];
    int iMin = -1, jMin = -1;
    double mvMatrix[16], projMatrix[16];
    double minDist = 1000;

    for (int a = 0; a < 8; a++, j -= 1.5) {
        for (int b = 0; b < 8; b++, i += 1.5) {

            // Світові x, y, z поточної шашки:
            double wx = i + 0.75;
            double wy = 0.6;
            double wz = j - 0.75;
            // Заповнюємо масив viewport поточною областю перегляду:
            glGetIntegerv(GL_VIEWPORT, viewport);

            // Заповнюємо масиви поточними матрицями:
            glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
            glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

            // Світові x, y, z координати, що обертаються:
            double dx, dy, dz;

            // Отримуємо координати точки, на яку спроектовано поточну шашку:
            gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
            dy = viewport[3] - dy - 1; // dy необхідно перерахувати
            double d = (x - dx) * (x - dx) + (y - dy) * (y - dy); // квадрат відстані
            if (d < minDist) // знайшли ближчий ближчу
            {
                minDist = d;
                iMin = b;
                jMin = a;
            }
        }
        i = 0.0;
    }
    if (minDist < 1000) // знайшли найближчу шашку
    {
        x1 = jMin;
        z1 = iMin;
        return true;
    }
    else
    {
        return false;
    }
}
void Scene::drawCell() {
    float i = 0.0;
    float j = 0.0;
    for (int x = 0; x < 8; x++, j -= 1.5) {
        for (int y = 0; y < 8; y++, i += 1.5) {
            switch (getColor(x, y))
            {
            case 0:
                break;
            case 1:
                glPushMatrix();
                glTranslatef(i + 0.75, 0.6, j - 0.75);
                if (getSelect(x, y) == true) {
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else {
                    glColor3f(0.05f, 0.05f, 0.05f);
                }
                draw_Cylinder();
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(i + 0.75, 0.6, j - 0.75);
                if (getSelect(x, y) == true) {
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else {
                    glColor3f(1.0f, 1.0f, 1.0f);
                }
                draw_Cylinder();
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(i + 0.75, 0.6, j - 0.75);
                if (getSelect(x, y) == true) {
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else {
                    glColor3f(0.05f, 0.05f, 0.05f);
                }
                draw_Queen();
                glPopMatrix();
                break;
            case 4:
                glPushMatrix();
                glTranslatef(i + 0.75, 0.6, j - 0.75);
                if (getSelect(x, y) == true) {
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else {
                    glColor3f(1.0f, 1.0f, 1.0f);
                }
                draw_Queen();
                glPopMatrix();
                break;
            }

        }
        i = 0.0;
    }
}
void Scene::on_mouse(int button, int state, int x, int y) {
    if ((state == GLUT_UP)) // кнопка віджата
    {
        int a, b;
        if (findNearest(x, y, a, b) == true) {
            setCelectedCell(a, b, rotate_round, round);
            glutPostRedisplay();
        }
        glutPostRedisplay();
    }
}
void Scene::processSpecialKeys(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_F1:
        restart();
        break;
    case GLUT_KEY_RIGHT:
        rotate_z -= 5;
        break;
    case GLUT_KEY_LEFT:
        rotate_z += 5;
        break;
    case GLUT_KEY_UP:
        rotate_x -= 5;
        break;
    case GLUT_KEY_DOWN:
        rotate_x += 5;
        break;
    }
    glutPostRedisplay();
}
void Scene::handleKeypress(unsigned char key, int x, int y) {
    switch (key)
    {
    case 27:
        exit(0);
    case '+':
        rotate_y += 0.1;
        break;
    case '-':
        rotate_y -= 0.1;
        break;
    }
}
void Scene::handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, (double)w / (double)h, 1.0, 200);
    gluLookAt(0.0f, 5.5f, 15.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);
}
void Scene::drawString(void* font, const char* text, float x, float y) {
    if (!text) // Немає тексту
    {
        return;
    }
    // Встановлення позиції тексту:
    glRasterPos2f(x, y);
    while (*text)
    {
        // Рядок виводиться посимвольно:
        glutBitmapCharacter(font, *text);
        text++;
    }
}
void Scene::on_paint() {
    Win();
    char text[128];
    char text1[128];
    char text2[128];
    char text3[128];
    sprintf_s(text3, "F1 - Restart");
    if (winner == -1) {
        sprintf_s(text, "Esc - Exit               Time: %d sec.", time);
        sprintf_s(text1, " Black: %d", winBlack);
        sprintf_s(text2, "White: %d", winWhite);
    }
    else if (winner == 1) {
        sprintf_s(text, "Esc - Exit             White Win               Time: %d sec.", time);
        sprintf_s(text1, " Black: %d", winBlack);
        sprintf_s(text2, "White: %d", winWhite + 1);
    }
    else if (winner == 2) {
        sprintf_s(text, "Esc - Exit              Black Win               Time: %d sec.", time);
        sprintf_s(text1, " Black: %d", winBlack + 1);
        sprintf_s(text2, "White: %d", winWhite);
    }
    static int k = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //For text
    glOrtho(0, 1, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1, 1, 0); //Yellow text
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, -8.0, 9.0);
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, text1, -13.0, -13.0);
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, text2, -13.0, -14.5);
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, text3, -8.2, 8.2);
    glPopMatrix();

    glTranslatef(0, 0, rotate_y);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    glRotatef(rotate_round, 0.0, 1.0, 0.0);
    glTranslatef(-4 * 1.5, 0.0, 4 * 1.5);
    for (float j = 0.0; j > (-8 * 1.5); j -= 1.5, k++)
    {
        for (float i = 0.0; i < (4 * 3.0); i += 3.0)
        {
            if (k % 2 == 0)
            {
                glPushMatrix();
                glTranslatef(i, 0.0, j);
                glColor3f(0.5f, 0.05f, 0.05f);
                draw_Box();
                glPopMatrix();

            }
            else
            {
                glPushMatrix();
                glTranslatef(i + 1.5, 0.0, j);
                glColor3f(0.5f, 0.05f, 0.05f);
                draw_Box();
                glPopMatrix();

            }
        }
    }
    for (float j = 0.0; j > (-8 * 1.5); j -= 1.5, k++)
    {
        for (float i = 0.0; i < (4 * 3.0); i += 3.0)
        {
            if (k % 2 != 0)
            {
                glPushMatrix();
                glTranslatef(i, 0.0, j);
                glColor3f(0.05f, 0.5f, 0.05f);
                draw_Box();
                glPopMatrix();

            }
            else
            {
                glPushMatrix();
                glTranslatef(i + 1.5, 0.0, j);
                glColor3f(0.05f, 0.5f, 0.05f);
                draw_Box();
                glPopMatrix();

            }
        }
    }
    drawCell();
    glutSwapBuffers();
}
int tick = 0;
void Scene::on_timer(int value)
{
    tick++;
    if (winner == -1) {
        if (tick >= 40) // нарахували наступну секунду
        {
            time++;
            tick = 0;   // скинули лічильник
        }
    }
    on_paint();     // здійснюємо перемалювання вікна
}
void  Scene::restart() {
    rotate_z = 0;
    rotate_x = 0;
    rotate_round = 0;
    round = 0;
    winner = -1;
    time = 0;
    rotate_y = 0.0;
    std::ifstream fin("Winners.txt");
    fin >> winWhite;
    fin >> winBlack;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gameBoard[i][j].select = false;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gameBoard[i][j].color = EMPTY;
            gameBoard[i][j].x = i;
            gameBoard[i][j].y = j;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if (j % 2 == 0 && i % 2 == 0) {
                gameBoard[i][j].color = WHITE;
                gameBoard[i][j].x = i;
                gameBoard[i][j].y = j;
            }
            else if (i % 2 != 0 && j % 2 != 0) {
                gameBoard[i][j].color = WHITE;
                gameBoard[i][j].x = i;
                gameBoard[i][j].y = j;
            }
        }
    }
    for (int i = 7; i > 4; i--) {
        for (int j = 0; j < 8; j++) {
            if (j % 2 == 0 && i % 2 == 0) {
                gameBoard[i][j].color = BLACK;
                gameBoard[i][j].x = i;
                gameBoard[i][j].y = j;
            }
            else if (i % 2 != 0 && j % 2 != 0) {
                gameBoard[i][j].color = BLACK;
                gameBoard[i][j].x = i;
                gameBoard[i][j].y = j;
            }
        }
    }
    glutPostRedisplay();
}