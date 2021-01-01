#pragma once
#include "glut.h"
#include "Board.h"
#include "Checker.h"
#include "Game.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
class Scene : public Game
{
private:
	int rotate_round = 0;
	int rotate_z = 0, rotate_x = 0;
	float rotate_y = 0.0;
	int time;
	int round = 0;
public:
	Scene() {
		Game game;
	}
	void on_mouse(int button, int state, int x, int y);
	void on_paint();
	void on_timer(int value);
	bool findNearest(int x, int y, int& x1, int& z1);
	void drawCell();
	void processSpecialKeys(int key, int x, int y);
	void handleKeypress(unsigned char key, int x, int y);
	void handleResize(int w, int h);
	void drawString(void* font, const char* text, float x, float y);
	void restart();
};

