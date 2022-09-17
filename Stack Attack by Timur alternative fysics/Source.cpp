#include <iostream>
#include <random>
#include <thread>
#include <malloc.h>
#include <windows.h>
#include <conio.h>
#include <ctime>

#define HEIGH_ROOM 10
#define WIDTH_ROOM 12

int ROOM[WIDTH_ROOM][HEIGH_ROOM];
bool exiting = false;
bool flying = false;
int playerPosX = rand() % WIDTH_ROOM;
int playerPosY = 0;
long long JumpTime;
int score = 0;
int NewBlockPosX;
int NewBlockPosY;

bool MayMoveBlock(int room[WIDTH_ROOM][HEIGH_ROOM], int x1, int x2, int y) {
	if ((room[x2][y] == 0) && (room[x1][y + 1] == 0) && (x2 >= 0) && (x2 < WIDTH_ROOM)) {
		return(true);
	}
	else return(false);
}
bool IfDropping(int room[WIDTH_ROOM][HEIGH_ROOM], int x, int y) {
	if ((room[x][y - 1] == 0) && (y - 1 >= 0)) {
		return(true);
	}
	else return(false);
}
void DebagWriting() {
	while (1 && !exiting) {
		std::cout << "SCORE: " << score << "\n";
		for (int j = HEIGH_ROOM - 1; j >= 0; j--) {
			for (int i = 0; i < WIDTH_ROOM; i++) {
				std::cout << ROOM[i][j] << "     ";
			}
			std::cout << "\n";
		}
		std::cout << "\n" << "\n" << "\n";
		Sleep(1000);
	}
}
void MoveBlock(int room[WIDTH_ROOM][HEIGH_ROOM], int x1, int y1, int x2, int y2) {
	room[x2][y2] = room[x1][y1];
	room[x1][y1] = 0;
}
void SpawnNewBlocks() {
	while (1 && !exiting) {
		NewBlockPosX = rand() % WIDTH_ROOM;
		NewBlockPosY = HEIGH_ROOM - 1;
		ROOM[NewBlockPosX][NewBlockPosY] = rand() % 3 + 1;
		while (IfDropping(ROOM, NewBlockPosX, NewBlockPosY)) {
			MoveBlock(ROOM, NewBlockPosX, NewBlockPosY, NewBlockPosX, NewBlockPosY - 1);
			NewBlockPosY--;
			Sleep(1000);
			if (ROOM[NewBlockPosX][NewBlockPosY - 1] == 9) {
				exiting = true;
				std::cout << "\n\n\n\n\n";
				std::cout << "GAME OVER" << "\n";
				std::cout << "Your score: " << score;
				break;
			}
		}
	}
}
void ButtonCheck() {
	while (1) {
		char ch;
		int code;
		ch = _getche();
		code = static_cast<int>(ch);
		if (ch == 27) {// если клавиша esc
			exiting = true;
			std::cout << "EXITING";
			break;
		}
		if ((ch == 65) || (ch == 97)) { // если клавиша A
			//std::cout << "A";
			if ((ROOM[playerPosX - 1][playerPosY] == 0) && (ROOM[playerPosX - 1][playerPosY + 1] == 0) && (playerPosX - 1 >= 0)) {
				//std::cout << "A";
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX - 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX - 1, playerPosY + 1);
				playerPosX--;
			}
		}
		if ((ch == 68) || (ch == 100)) { // если клавиша D
			//std::cout << "D";
			if ((ROOM[playerPosX + 1][playerPosY] == 0) && (ROOM[playerPosX + 1][playerPosY + 1] == 0) && (playerPosX + 1 < WIDTH_ROOM)) {
				//std::cout << "D";
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX + 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX + 1, playerPosY + 1);
				playerPosX++;
			}
		}
		if (ch == 32) {
			std::cout << "SPACE";
			if (clock() / CLK_TCK - JumpTime >= 3) {
				std::cout << "jump";
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX, playerPosY + 2);
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX, playerPosY + 1);
				playerPosY++;
				JumpTime = clock() / CLK_TCK;
			}
		}
	}
}


int main() {

	for (int j = 0; j < HEIGH_ROOM; j++) {
		for (int i = 0; i < WIDTH_ROOM; i++) {
			ROOM[i][j] = 0;
		}
	}
	for (int i = 0; i < WIDTH_ROOM; i++) {
		if (i != playerPosX) ROOM[i][0] = rand() % 4;
	}
	ROOM[playerPosX][playerPosY] = 9;
	ROOM[playerPosX][playerPosY + 1] = 9;
	std::thread SpawnBlocks(SpawnNewBlocks);
	//#ifdef DEBUG
	std::thread DEBUGth(DebagWriting);
	//#endif
	//std::thread Buttons(ButtonCheck);
	time_t timeESC = 0;
	time_t timeA = 0;
	time_t timeD = 0;
	time_t timeSPACE = 0;
	while (1) { // main cycle
		if ((GetKeyState(27) & 0x8000) && (clock() / CLK_TCK - timeESC >= 1)) {// если клавиша esc
			timeESC = clock() / CLK_TCK;
			exiting = true;
			std::cout << "EXITING";
			break;
		}
		if ((GetKeyState('A') & 0x8000) && (clock() / CLK_TCK - timeA >= 1)) { // если клавиша A
			timeA = clock() / CLK_TCK;
			//std::cout << "A";
			if ((ROOM[playerPosX - 1][playerPosY] == 0) && (ROOM[playerPosX - 1][playerPosY + 1] == 0) && (playerPosX - 1 >= 0)) {
				//std::cout << "LeftMove";
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX - 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX - 1, playerPosY + 1);
				playerPosX--;
			}
			else if ((MayMoveBlock(ROOM, playerPosX - 1, playerPosX - 2, playerPosY)) && (clock() / CLK_TCK - JumpTime >= 3)) {
				std::cout << "LeftPush";
				MoveBlock(ROOM, playerPosX - 1, playerPosY, playerPosX - 2, playerPosY);
				int BlockPosY = playerPosY;
				while (IfDropping(ROOM, playerPosX - 2, BlockPosY)) {
					//std::cout << "drop";
					MoveBlock(ROOM, playerPosX - 2, BlockPosY, playerPosX - 2, BlockPosY - 1);
					BlockPosY--;
				}

				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX - 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX - 1, playerPosY + 1);
				playerPosX--;
			}
		}
		if ((GetKeyState('D') & 0x8000) && (clock() / CLK_TCK - timeD >= 1)) { // если клавиша D
			timeD = clock() / CLK_TCK;
			//std::cout << "D";
			if ((ROOM[playerPosX + 1][playerPosY] == 0) && (ROOM[playerPosX + 1][playerPosY + 1] == 0) && (playerPosX + 1 < WIDTH_ROOM)) {
				//std::cout << "RightMove";
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX + 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX + 1, playerPosY + 1);
				playerPosX++;
			}
			else if ((MayMoveBlock(ROOM, playerPosX + 1, playerPosX + 2, playerPosY)) && (clock() / CLK_TCK - JumpTime >= 3)) {
				std::cout << "RightPush";
				MoveBlock(ROOM, playerPosX + 1, playerPosY, playerPosX + 2, playerPosY);
				int BlockPosY = playerPosY;
				while (IfDropping(ROOM, playerPosX + 2, BlockPosY)) {
					//std::cout << "drop";
					MoveBlock(ROOM, playerPosX + 2, BlockPosY, playerPosX + 2, BlockPosY - 1);
					BlockPosY--;
				}

				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX + 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX + 1, playerPosY + 1);
				playerPosX++;
			}
		}
		if ((GetKeyState(32) & 0x8000) && (clock() / CLK_TCK - timeSPACE >= 1)) {
			timeSPACE = clock() / CLK_TCK;
			//std::cout << "SPACE";
			if (clock() / CLK_TCK - JumpTime >= 4) {
				//std::cout << "jump";
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX, playerPosY + 2);
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX, playerPosY + 1);
				playerPosY++;
				JumpTime = clock() / CLK_TCK;
			}
		}
		if (clock() / CLK_TCK - JumpTime >= 3) {
			while (IfDropping(ROOM, playerPosX, playerPosY)) {
				//std::cout << "drop";
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX, playerPosY - 1);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX, playerPosY);
				playerPosY--;
			}
		}
		if (clock() / CLK_TCK % 1 == 0) {
			bool ifZero = false;
			for (int i = 0; i < WIDTH_ROOM; i++) {
				if (ROOM[i][0] == 0 || ROOM[i][0] == 9) {
					ifZero = true;
					break;
				}
			}
			if (!ifZero) {
				score++;
				for (int i = 1; i < HEIGH_ROOM; i++) {
					for (int j = 0; j < WIDTH_ROOM; j++) {
						if (((i != NewBlockPosY) && (i != NewBlockPosY + 1)) || (j != NewBlockPosX))
							MoveBlock(ROOM, j, i, j, i - 1);
					}
				}
				playerPosY--;
			}
		}
		/*
		if (ROOM[playerPosX][playerPosY + 2] != 0) {
			exiting = true;
			std::cout << "\n\n\n\n\n";
			std::cout << "GAME OVER" << "\n";
			std::cout << "Your score: " << score;
			break;
		}*/
	}

	//Buttons.join();
	SpawnBlocks.join();
	DEBUGth.join();
}
