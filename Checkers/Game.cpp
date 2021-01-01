#include "Game.h"
#include "glut.h"
#include <vector>
#include <iostream>
#include <fstream>
Game::Type Game::getColor(int x, int y) {
	return gameBoard[x][y].color;
}
bool Game::getSelect(int x, int y) {
	return gameBoard[x][y].select;
}
void Game::setCelectedCell(int a, int b, int& round_rotate, int& round) {
	if ((gameBoard[a][b].color == WHITE || gameBoard[a][b].color == QUEEN_WHITE) && round % 2 == 0) {
		gameBoard[a][b].select = true;
		selectedCell.push_back(gameBoard[a][b]);
		if (selectedCell.size() > 1) {
			int x, y;
			x = selectedCell[selectedCell.size() - 2].x;
			y = selectedCell[selectedCell.size() - 2].y;
			gameBoard[x][y].select = false;
		}
	}
	else if ((gameBoard[a][b].color == BLACK || gameBoard[a][b].color == QUEEN_BLACK) && round % 2 != 0) {
		gameBoard[a][b].select = true;
		selectedCell.push_back(gameBoard[a][b]);
		if (selectedCell.size() > 1) {
			int x, y;
			x = selectedCell[selectedCell.size() - 2].x;
			y = selectedCell[selectedCell.size() - 2].y;
			gameBoard[x][y].select = false;
		}
	}
	else if (selectedCell.size() > 0 && gameBoard[a][b].color == EMPTY) {
		int x = selectedCell[selectedCell.size() - 1].x;
		int y = selectedCell[selectedCell.size() - 1].y;
		if (gameBoard[x][y].color == BLACK || gameBoard[x][y].color == WHITE) {
			if (getJump(a, b) == true) {
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].color = EMPTY;
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].select = false;
				selectedCell[selectedCell.size() - 1].select = false;
				gameBoard[a][b].color = selectedCell[selectedCell.size() - 1].color;
				gameBoard[a][b].x = a;
				gameBoard[a][b].y = b;
				if (moreJumps(gameBoard[a][b].x, gameBoard[a][b].y) == false) {
					selectedCell.clear();
					round_rotate += 180;
					round += 1;
				}
				if (a == 0) {
					gameBoard[a][b].color = QUEEN_BLACK;
					gameBoard[a][b].x = a;
					gameBoard[a][b].y = b;
					selectedCell.clear();
				}
				else if (a == 7) {
					gameBoard[a][b].color = QUEEN_WHITE;
					gameBoard[a][b].x = a;
					gameBoard[a][b].y = b;
					selectedCell.clear();
				}
			}
			else if (simpleStep(a, b) == true && canAttack(round) == false) {
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].color = EMPTY;
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].select = false;
				selectedCell[selectedCell.size() - 1].select = false;
				gameBoard[a][b] = selectedCell[selectedCell.size() - 1];
				gameBoard[a][b].x = a;
				gameBoard[a][b].y = b;
				selectedCell.clear();
				round_rotate += 180;
				round += 1;
				if (a == 0) {
					gameBoard[a][b].color = QUEEN_BLACK;
					gameBoard[a][b].x = a;
					gameBoard[a][b].y = b;
					selectedCell.clear();
				}
				else if (a == 7) {
					gameBoard[a][b].color = QUEEN_WHITE;
					gameBoard[a][b].x = a;
					gameBoard[a][b].y = b;
					selectedCell.clear();
				}
			}
		}
		else if (gameBoard[x][y].color == QUEEN_BLACK || gameBoard[x][y].color == QUEEN_WHITE) {
			if (getJumpQueen(a, b) == true) {
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].color = EMPTY;
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].select = false;
				selectedCell[selectedCell.size() - 1].select = false;
				gameBoard[a][b].color = selectedCell[selectedCell.size() - 1].color;
				gameBoard[a][b].x = a;
				gameBoard[a][b].y = b;
				if (moreJumpsQueen(a, b) == false) {
					selectedCell.clear();
					round_rotate += 180;
					round += 1;
				}
			}
			else if (simpleStep(a, b) == true && canAttack(round) == false) {
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].color = EMPTY;
				gameBoard[selectedCell[selectedCell.size() - 1].x][selectedCell[selectedCell.size() - 1].y].select = false;
				selectedCell[selectedCell.size() - 1].select = false;
				gameBoard[a][b].color = selectedCell[selectedCell.size() - 1].color;
				gameBoard[a][b].x = a;
				gameBoard[a][b].y = b;
				selectedCell.clear();
				round_rotate += 180;
				round += 1;
			}
		}
	}
}
bool Game::simpleStep(int a, int b) {
	int x, y;
	x = selectedCell[selectedCell.size() - 1].x;
	y = selectedCell[selectedCell.size() - 1].y;
	if (gameBoard[x][y].color == WHITE) {
		if ((a == x + 1 && b == y + 1) || (a == x + 1 && b == y - 1))
			return true;
	}
	else if (gameBoard[x][y].color == BLACK) {
		if ((a == x - 1 && b == y - 1) || (a == x - 1 && b == y + 1))
			return true;
	}
	else if (gameBoard[x][y].color == QUEEN_WHITE || gameBoard[x][y].color == QUEEN_BLACK) {
		std::vector<Cell> numbBlackCell;
		std::vector<Cell> numbWhiteCell;
		if (abs(x - a) == abs(y - b)) {
			if (a > x && b > y) {
				for (int i = x + 1, j = y + 1; i < a; i++, j++) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a > x && b < y) {
				for (int i = x + 1, j = y - 1; i < a; i++, j--) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a < x&& b < y) {
				for (int i = x - 1, j = y - 1; i > a; i--, j--) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a < x && b > y) {
				for (int i = x - 1, j = y + 1; i > a; i--, j++) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
		}
		if (numbWhiteCell.size() == 0 && numbBlackCell.size() == 0) {
			return true;
		}
		numbWhiteCell.clear();
		numbBlackCell.clear();
	}
	return false;
}
bool Game::getJump(int a, int b) {
	int x, y;
	x = selectedCell[selectedCell.size() - 1].x;
	y = selectedCell[selectedCell.size() - 1].y;
	if (gameBoard[x][y].color == WHITE) {
		if (a == x - 2 && b == y + 2 && (gameBoard[x - 1][y + 1].color == BLACK || gameBoard[x - 1][y + 1].color == QUEEN_BLACK)) {
			gameBoard[x - 1][y + 1].color = EMPTY;
			return true;
		}
		else if (a == x - 2 && b == y - 2 && (gameBoard[x - 1][y - 1].color == BLACK || gameBoard[x - 1][y - 1].color == QUEEN_BLACK)) {
			gameBoard[x - 1][y - 1].color = EMPTY;
			return true;
		}
		else if (a == x + 2 && b == y + 2 && (gameBoard[x + 1][y + 1].color == BLACK || gameBoard[x + 1][y + 1].color == QUEEN_BLACK)) {
			gameBoard[x + 1][y + 1].color = EMPTY;
			return true;
		}
		else if (a == x + 2 && b == y - 2 && (gameBoard[x + 1][y - 1].color == BLACK || gameBoard[x + 1][y - 1].color == QUEEN_BLACK)) {
			gameBoard[x + 1][y - 1].color = EMPTY;
			return true;
		}
	}
	else if (gameBoard[x][y].color == BLACK) {
		if (a == x - 2 && b == y + 2 && (gameBoard[x - 1][y + 1].color == WHITE || gameBoard[x - 1][y + 1].color == QUEEN_WHITE)) {
			gameBoard[x - 1][y + 1].color = EMPTY;
			return true;
		}
		else if (a == x - 2 && b == y - 2 && (gameBoard[x - 1][y - 1].color == WHITE || gameBoard[x - 1][y - 1].color == QUEEN_WHITE)) {
			gameBoard[x - 1][y - 1].color = EMPTY;
			return true;
		}
		else if (a == x + 2 && b == y + 2 && (gameBoard[x + 1][y + 1].color == WHITE || gameBoard[x + 1][y + 1].color == QUEEN_WHITE)) {
			gameBoard[x + 1][y + 1].color = EMPTY;
			return true;
		}
		else if (a == x + 2 && b == y - 2 && (gameBoard[x + 1][y - 1].color == WHITE || gameBoard[x + 1][y - 1].color == QUEEN_WHITE)) {
			gameBoard[x + 1][y - 1].color = EMPTY;
			return true;
		}
	}
}
bool Game::getJumpQueen(int a, int b) {
	std::vector<Cell> numbBlackCell;
	std::vector<Cell> numbWhiteCell;
	int x, y;
	x = selectedCell[selectedCell.size() - 1].x;
	y = selectedCell[selectedCell.size() - 1].y;
	if (abs(x - a) == abs(y - b)) {
		if (gameBoard[x][y].color == QUEEN_BLACK) {
			if (a > x && b > y) {
				for (int i = x + 1, j = y + 1; i < a; i++, j++) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a > x && b < y) {
				for (int i = x + 1, j = y - 1; i < a; i++, j--) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a < x&& b < y) {
				for (int i = x - 1, j = y - 1; i > a; i--, j--) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a < x && b > y) {
				for (int i = x - 1, j = y + 1; i > a; i--, j++) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			if (numbWhiteCell.size() == 1 && numbBlackCell.size() == 0) {
				int z, s;
				z = numbWhiteCell[numbWhiteCell.size() - 1].x;
				s = numbWhiteCell[numbWhiteCell.size() - 1].y;
				gameBoard[z][s].color = EMPTY;
				numbWhiteCell.clear();
				numbBlackCell.clear();
				return true;
			}
		}
		else if (gameBoard[x][y].color == QUEEN_WHITE) {
			if (a > x && b > y) {
				for (int i = x + 1, j = y + 1; i < a; i++, j++) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a > x && b < y) {
				for (int i = x + 1, j = y - 1; i < a; i++, j--) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a < x&& b < y) {
				for (int i = x - 1, j = y - 1; i > a; i--, j--) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			else if (a < x && b > y) {
				for (int i = x - 1, j = y + 1; i > a; i--, j++) {
					if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE)
						numbWhiteCell.push_back(gameBoard[i][j]);
					else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK)
						numbBlackCell.push_back(gameBoard[i][j]);
				}
			}
			if (numbWhiteCell.size() == 0 && numbBlackCell.size() == 1) {
				int z, s;
				z = numbBlackCell[numbBlackCell.size() - 1].x;
				s = numbBlackCell[numbBlackCell.size() - 1].y;
				gameBoard[z][s].color = EMPTY;
				numbWhiteCell.clear();
				numbBlackCell.clear();
				return true;
			}
		}
	}
	numbWhiteCell.clear();
	numbBlackCell.clear();
	return false;
}
bool Game::moreJumps(int a, int b) {
	if (gameBoard[a][b].color == WHITE) {
		if ((gameBoard[a + 1][b + 1].color == BLACK || gameBoard[a + 1][b + 1].color == QUEEN_BLACK) && a + 2 < 8 && b + 2 < 8) {
			if (gameBoard[a + 2][b + 2].color == EMPTY)
				return true;
		}
		if ((gameBoard[a - 1][b + 1].color == BLACK || gameBoard[a - 1][b + 1].color == QUEEN_BLACK) && a - 2 >= 0 && b + 2 < 8) {
			if (gameBoard[a - 2][b + 2].color == EMPTY)
				return true;
		}
		if ((gameBoard[a + 1][b - 1].color == BLACK || gameBoard[a + 1][b - 1].color == QUEEN_BLACK) && a + 2 < 8 && b - 2 >= 0) {
			if (gameBoard[a + 2][b - 2].color == EMPTY)
				return true;
		}
		if ((gameBoard[a - 1][b - 1].color == BLACK || gameBoard[a - 1][b - 1].color == QUEEN_BLACK) && a - 2 >= 0 && b - 2 >= 0) {
			if (gameBoard[a - 2][b - 2].color == EMPTY)
				return true;
		}
		return false;
	}
	else if (gameBoard[a][b].color == BLACK) {
		if ((gameBoard[a + 1][b + 1].color == WHITE || gameBoard[a + 1][b + 1].color == QUEEN_WHITE) && (a + 2) < 8 && (b + 2) < 8) {
			if (gameBoard[a + 2][b + 2].color == EMPTY)
				return true;
		}
		if ((gameBoard[a - 1][b + 1].color == WHITE || gameBoard[a - 1][b + 1].color == QUEEN_WHITE) && (a - 2) >= 0 && (b + 2) < 8) {
			if (gameBoard[a - 2][b + 2].color == 0)
				return true;
		}
		if ((gameBoard[a + 1][b - 1].color == WHITE || gameBoard[a + 1][b - 1].color == QUEEN_WHITE) && (a + 2) < 8 && (b - 2) >= 0) {
			if (gameBoard[a + 2][b - 2].color == EMPTY)
				return true;
		}
		if ((gameBoard[a - 1][b - 1].color == WHITE || gameBoard[a - 1][b - 1].color == QUEEN_WHITE) && (a - 2) >= 0 && (b - 2) >= 0) {
			if (gameBoard[a - 2][b - 2].color == EMPTY)
				return true;
		}
	}
	return false;
}
bool Game::moreJumpsQueen(int a, int b) {
	if (gameBoard[a][b].color == QUEEN_BLACK) {
		for (int i = a + 1, j = b + 1; i < 8 && j < 8; i++, j++) {
			if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				if (gameBoard[i + 1][j + 1].color == EMPTY && i + 1 < 8 && j + 1 < 8)
					return true;
			}
			else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				break;
			}
		}
		for (int i = a + 1, j = b - 1; i < 8 && j > -1; i++, j--) {
			if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				if (gameBoard[i + 1][j - 1].color == EMPTY && i + 1 < 8 && j - 1 > -1)
					return true;
			}
			else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				break;
			}
		}
		for (int i = a - 1, j = b - 1; i > -1 && j > -1; i--, j--) {
			if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				if (gameBoard[i - 1][j - 1].color == EMPTY && i - 1 > -1 && j - 1 > -1)
					return true;
			}
			else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				break;
			}
		}
		for (int i = a - 1, j = b + 1; i > -1 && j < 8; i--, j++) {
			if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				if (gameBoard[i - 1][j + 1].color == EMPTY && i - 1 > -1 && j + 1 < 8)
					return true;
			}
			else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				break;
			}
		}
		return false;
	}
	else if (gameBoard[a][b].color == QUEEN_WHITE) {
		for (int i = a + 1, j = b + 1; i < 8 && j < 8; i++, j++) {
			if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				if (gameBoard[i + 1][j + 1].color == EMPTY && i + 1 < 8 && j + 1 < 8) {
					return true;
				}
				else {
					break;
				}
			}
			else if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				break;
			}
		}
		for (int i = a + 1, j = b - 1; i < 8 && j > -1; i++, j--) {
			if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				if (gameBoard[i + 1][j - 1].color == EMPTY && i + 1 < 8 && j - 1 > -1) {
					return true;
				}
				else {
					break;
				}
			}
			else if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				break;
			}
		}
		for (int i = a - 1, j = b - 1; i > -1 && j > -1; i--, j--) {
			if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				if (gameBoard[i - 1][j - 1].color == EMPTY && i - 1 > -1 && j - 1 > -1) {
					return true;
				}
				else {
					break;
				}
			}
			else if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				break;
			}
		}
		for (int i = a - 1, j = b + 1; i > -1 && j < 8; i--, j++) {
			if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				if (gameBoard[i - 1][j + 1].color == EMPTY && i - 1 > -1 && j + 1 < 8) {
					return true;
				}
				else {
					break;
				}
			}
			else if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				break;
			}
		}
		return false;
	}
	return false;
}
bool Game::canAttack(int round) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (round % 2 == 0) {
				if ((gameBoard[i][j].color == WHITE && moreJumps(i, j) == true) || (gameBoard[i][j].color == QUEEN_WHITE && moreJumpsQueen(i, j) == true)) {
					return true;
				}
			}
			else if (round % 2 != 0) {
				if ((gameBoard[i][j].color == BLACK && moreJumps(i, j) == true) || (gameBoard[i][j].color == QUEEN_BLACK && moreJumpsQueen(i, j) == true)) {
					return true;
				}
			}
		}
	}
	return false;
}
void Game::Win() {
	std::vector<Cell> White;
	std::vector<Cell> Black;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gameBoard[i][j].color == QUEEN_WHITE || gameBoard[i][j].color == WHITE) {
				White.push_back(gameBoard[i][j]);
			}
			else if (gameBoard[i][j].color == QUEEN_BLACK || gameBoard[i][j].color == BLACK) {
				Black.push_back(gameBoard[i][j]);
			}
		}
	}
	if (White.size() > 0 && Black.size() == 0) {
		std::ofstream fout("Winners.txt");
		fout << winWhite + 1 << std::endl;
		fout << winBlack;
		winner = 1;
	}
	else if (Black.size() > 0 && White.size() == 0) {
		std::ofstream fout("Winners.txt");
		fout << winWhite << std::endl;
		fout << winBlack + 1;
		winner = 2;
	}
}
