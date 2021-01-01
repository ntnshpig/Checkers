#pragma once
#include "Checker.h"
#include "Board.h"
#include <vector>
#include <fstream>
#include <iomanip>
class Game : public Checker, public Board
{
protected:
	int winner = -1;
	int winBlack, winWhite;
	enum Type { EMPTY = 0, BLACK = 1, WHITE = 2, QUEEN_BLACK = 3, QUEEN_WHITE = 4 };
	struct Cell
	{
		Type color;
		bool select;
		int x, y;
	};
	Cell gameBoard[8][8];
	std::vector<Cell> selectedCell;
public:
	Game() {
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
	}
	Type getColor(int x, int y);
	bool getSelect(int x, int y);
	void setCelectedCell(int a, int b, int& round_rotate, int& round);
	bool simpleStep(int a, int b);
	bool getJump(int a, int b);
	bool getJumpQueen(int a, int b);
	bool moreJumps(int a, int b);
	bool moreJumpsQueen(int a, int b);
	bool canAttack(int round);
	void Win();
};

