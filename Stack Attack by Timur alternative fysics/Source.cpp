#include <iostream>
#include <random>
#include <thread>
#include <malloc.h>
#include <windows.h>
//#include <conio.h>
#include <ctime>
//#include <Mmsystem.h>


#define HEIGH_ROOM 30
#define WIDTH_ROOM 12

int ROOM[WIDTH_ROOM][HEIGH_ROOM];
bool exiting = false;
bool flying = false;
int playerPosX = rand() % WIDTH_ROOM;
int playerPosY = 0;
long long JumpTime;
int score = 0;
int GameSpeed = 1000;

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
void MoveBlock(int room[WIDTH_ROOM][HEIGH_ROOM], int x1, int y1, int x2, int y2) {
	room[x2][y2] = room[x1][y1];
	room[x1][y1] = 0;
}
void SpawnNewBlocks() {
	while (1 && !exiting) {
		int NewBlockPosX;
		int NewBlockPosY;
		NewBlockPosX = rand() % WIDTH_ROOM;
		NewBlockPosY = HEIGH_ROOM - 1;
		ROOM[NewBlockPosX][NewBlockPosY] = rand() % 3 + 1;
		Sleep(GameSpeed*5);
	}
}
void DebagWriting() {
	while (1 && !exiting) {
		std::cout << "SCORE: " << score << " ";
		if (GameSpeed == 1000)
			std::cout << "Game Speed: x1";
		else if (GameSpeed == 500)
			std::cout << "Game Speed: x2";
		else if (GameSpeed == 250)
			std::cout << "Game Speed: x4";
		else
			std::cout << "Game Speed: x8";
		std::cout << "\n";
		for (int j = 1; j < HEIGH_ROOM; j++) {
			for (int i = 0; i < WIDTH_ROOM; i++) {
				if (ROOM[i][j] != 9) {
					if (ROOM[i][j] != 0) {
						if (ROOM[i][j - 1] == 9) {
							exiting = true;
							std::cout << "\a\n\n\n\n\n";
							std::cout << "GAME OVER" << "\n";
							std::cout << "Your score: " << score << "\n";
							break;
						}
						if (IfDropping(ROOM, i, j))
							if (ROOM[i][j] != 9) {
								MoveBlock(ROOM, i, j, i, j - 1);
							}
					}
				}
			}
		}
		for (int j = HEIGH_ROOM - 1; j >= 0; j--) {
			for (int i = 0; i < WIDTH_ROOM; i++) {
				if (ROOM[i][j] == 0) {
					std::cout << "| |";
				}
				else if (ROOM[i][j] == 1) {
					std::cout << "(/)";
				}
				else if (ROOM[i][j] == 2) {
					std::cout << "(@)";
				}
				else if (ROOM[i][j] == 3) {
					std::cout << "(#)";
				}
				else if (ROOM[i][j] == 9) {
					std::cout << "-|-";
				}
				else {
					std::cout << ROOM[i][j];
				}
				std::cout << "     ";
			}
			std::cout << "\n";
		}
		std::cout << "\n" << "\n" << "\n";
		Sleep(GameSpeed);
	}
}
void DroppingBlocks() {
	while (1 && !exiting) {
		for (int j = 1; j < HEIGH_ROOM; j++) {
			for (int i = 0; i < WIDTH_ROOM; i++) {
				if (ROOM[i][j] != 9) {
					if (ROOM[i][j] != 0) {
						if (ROOM[i][j - 1] == 9) {
							exiting = true;
							std::cout << "\a\n\n\n\n\n";
							std::cout << "GAME OVER" << "\n";
							std::cout << "Your score: " << score;
							break;
						}
						if (IfDropping(ROOM, i, j))
							if (ROOM[i][j] != 9) {
								MoveBlock(ROOM, i, j, i, j - 1);
							}
					}
				}
			}
		}
		Sleep(GameSpeed);
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
	//std::thread BlocksDrop(DroppingBlocks);
	time_t timeTAB = 0;
	time_t timeESC = 0;
	time_t timeA = 0;
	time_t timeD = 0;
	time_t timeSPACE = 0;
	while (1) { // main cycle
		if ((GetKeyState(27) & 0x8000) && (clock() * 1. / CLK_TCK - timeESC >= 1.5)) {// если клавиша esc
			timeESC = clock() / CLK_TCK;
			exiting = true;
			std::cout << "\aEXITING...";
			break;
		}
		if ((GetKeyState(9) & 0x8000) && (clock() * 1. / CLK_TCK - timeTAB >= 1.5)) {// если клавиша TAB
			timeTAB = clock() / CLK_TCK;
			//MessageBeep(MB_OK);
			PlaySound(TEXT("D:\Sound_55962300 1662746220 (online-audio-converter.com).wav"), 0, SND_ASYNC);
			//std::cout << "TAB";
			if (GameSpeed == 1000)
				GameSpeed = 500;
			else if(GameSpeed == 500)
				GameSpeed = 250;
			else if (GameSpeed == 250)
				GameSpeed = 125;
			else
				GameSpeed = 1000;
		}
		if ((GetKeyState('A') & 0x8000) && (clock()*1. / CLK_TCK - timeA >= 1.5)) { // если клавиша A
			timeA = clock() / CLK_TCK;
			//std::cout << "A";
			if ((ROOM[playerPosX - 1][playerPosY] == 0) && (ROOM[playerPosX - 1][playerPosY + 1] == 0) && (playerPosX - 1 >= 0)) {
				//std::cout << "LeftMove";
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX - 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX - 1, playerPosY + 1);
				playerPosX--;
			}
			else if ((MayMoveBlock(ROOM, playerPosX - 1, playerPosX - 2, playerPosY)) && (clock() / CLK_TCK - JumpTime >= 3)) {
				//std::cout << "LeftPush";
				MoveBlock(ROOM, playerPosX - 1, playerPosY, playerPosX - 2, playerPosY);

				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX - 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX - 1, playerPosY + 1);
				playerPosX--;
			}
		}
		if ((GetKeyState('D') & 0x8000) && (clock() * 1. / CLK_TCK - timeD >= 1.5)) { // если клавиша D
			timeD = clock() / CLK_TCK;
			//std::cout << "D";
			if ((ROOM[playerPosX + 1][playerPosY] == 0) && (ROOM[playerPosX + 1][playerPosY + 1] == 0) && (playerPosX + 1 < WIDTH_ROOM)) {
				//std::cout << "RightMove";
				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX + 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX + 1, playerPosY + 1);
				playerPosX++;
			}
			else if ((MayMoveBlock(ROOM, playerPosX + 1, playerPosX + 2, playerPosY)) && (clock() / CLK_TCK - JumpTime >= 3)) {
				//std::cout << "RightPush";
				MoveBlock(ROOM, playerPosX + 1, playerPosY, playerPosX + 2, playerPosY);

				MoveBlock(ROOM, playerPosX, playerPosY, playerPosX + 1, playerPosY);
				MoveBlock(ROOM, playerPosX, playerPosY + 1, playerPosX + 1, playerPosY + 1);
				playerPosX++;
			}
		}
		if ((GetKeyState(32) & 0x8000) && (clock() * 1. / CLK_TCK - timeSPACE >= 1.5)) {
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
				MessageBeep(MB_OK);
				score++;
				for (int i = 0; i < WIDTH_ROOM; i++) {
					ROOM[i][0] = 0;
				}
			}
		}
	}
	//BlocksDrop.join();
	SpawnBlocks.join();
	DEBUGth.join();
}
