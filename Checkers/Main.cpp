#include "glut.h"
#include "Scene.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
Scene Checkers;
void on_paint() {
    Checkers.on_paint();
}
void on_mouse(int button, int state, int x, int y) {
    Checkers.on_mouse(button, state, x, y);
}
void handleResize(int w, int h) {
    Checkers.handleResize(w, h);
}
void handleKeypress(unsigned char key, int x, int y) {
    Checkers.handleKeypress(key, x, y);
}
void processSpecialKeys(int key, int x, int y) {
    Checkers.processSpecialKeys(key, x, y);
}
void on_timer(int value) {
    Checkers.on_timer(value);
    glutTimerFunc(25, on_timer, 0);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);

    glutCreateWindow("Checkers");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0f, 0.8f, 0.8f, 0.8f);

    glutDisplayFunc(on_paint);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(on_mouse);
    glutSpecialFunc(processSpecialKeys);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, on_timer, 0);
    glutMainLoop();

    return 0;

}