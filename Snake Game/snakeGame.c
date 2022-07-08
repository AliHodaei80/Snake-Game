#include <stdio.h>
#include <conio.h>
#include <time.h>
#define WIDTH 10
#define HEIGHT 10
#define true 1
#define false 0
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define APPLE WIDTH*HEIGHT+1
int speed = 0;

void findMaxLoc(int board[WIDTH][HEIGHT], int* max, int* iMax, int* jMax) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (board[i][j] > *max && board[i][j]!=APPLE) {
				*max = board[i][j];
				*iMax = i;
				*jMax = j;
			}
		}
	}
}
void dropApple(int board[WIDTH][HEIGHT]) {
	while (true){
		int i = rand() % WIDTH;
		int j = rand() % HEIGHT;
		if (board[i][j] == 0) {
			board[i][j] = APPLE;
			return;
		}
	}
}
void moveBody(int board[WIDTH][HEIGHT]) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (board[i][j] != 0 && board[i][j]!=APPLE) {
				board[i][j]--;
			}
		}
	}
}
int exitFromBoard(char ch, int iMax, int jMax) {
	if (ch == UP) {
		if (iMax == 0)
			return true;
	}
	else if (ch == DOWN) {
		if (iMax == WIDTH-1)
			return true;
	}
	else if (ch == LEFT) {
		if (jMax == 0)
			return true;
	}
	else {
		if (jMax == HEIGHT-1)
			return true;
	}
	return false;
}
int colideSelf(int board[WIDTH][HEIGHT], char ch, int iMax, int jMax) {
	if (ch == UP) {
		if (board[iMax - 1][jMax] != 0 && board[iMax - 1][jMax]!=APPLE)
			return true;
	}
	else if (ch == DOWN) {
		if (board[iMax + 1][jMax] != 0 && board[iMax + 1][jMax] != APPLE)
			return true;
	}
	else if (ch == LEFT) {
		if (board[iMax][jMax - 1] != 0 && board[iMax][jMax - 1] != APPLE)
			return true;
	}
	else {
		if (board[iMax][jMax + 1] != 0 && board[iMax][jMax + 1] != APPLE)
			return true;
	}
	return false;
}
int lose(int board[WIDTH][HEIGHT], char ch, int iMax, int jMax) {
	if (exitFromBoard(ch, iMax, jMax))
		return true;
	if (colideSelf(board, ch, iMax, jMax))
		return true;
	return false;
}
int win(int max) {
	if (max == WIDTH * HEIGHT - 1)
		return true;
	return false;
}
void printGameOver() {
	char c;
	printf("\nGame Over!");
	scanf_s("%c", &c,2);
}
void printWin() {
	char c;
	printf("\nYou Win!");
	scanf_s("%c", &c, 2);
}
void update(int board[WIDTH][HEIGHT], char ch) {
	int iMax, jMax;
	int max = 0;
	findMaxLoc(board, &max, &iMax, &jMax);
	if (lose(board, ch, iMax, jMax)) {
		printGameOver();
		exit(0);
	}
	if (ch == UP) {
		if (board[iMax - 1][jMax] == APPLE) {
			board[iMax - 1][jMax] = max + 1;
			speed += (WIDTH < HEIGHT ? WIDTH : HEIGHT);
			dropApple(board);
		}
		else {
			board[iMax - 1][jMax] = max + 1;
			moveBody(board);
		}
	}
	else if (ch == DOWN) {
		if (board[iMax + 1][jMax] == APPLE) {
			board[iMax + 1][jMax] = max + 1;
			speed += (WIDTH < HEIGHT ? WIDTH : HEIGHT);
			dropApple(board);
		}
		else {
			board[iMax + 1][jMax] = max + 1;
			moveBody(board);
		}
	}
	else if (ch == LEFT) {
		if (board[iMax][jMax - 1] == APPLE) {
			board[iMax][jMax - 1] = max + 1;
			speed += (WIDTH < HEIGHT ? WIDTH : HEIGHT);
			dropApple(board);
		}
		else {
			board[iMax][jMax - 1] = max + 1;
			moveBody(board);
		}
	}
	else {
		if (board[iMax][jMax + 1] == APPLE) {
			board[iMax][jMax + 1] = max + 1;
			speed += (WIDTH < HEIGHT ? WIDTH : HEIGHT);
			dropApple(board);
		}
		else {
			board[iMax][jMax + 1] = max + 1;
			moveBody(board);
		}
	}
	if (win(max)) {
		printWin();
		exit(0);
	}
}
void print(int board[WIDTH][HEIGHT]) {
	system("cls");
	printf("\033[96m%c\033[0m", 218);
	for (int i = 0; i < HEIGHT * 2 + 2; i++)printf("\033[96m%c\033[0m", 196);
	printf("\033[96m%c\n\033[0m", 191);
	for (int i = 0; i < WIDTH; i++) {
		printf("\033[96m%c \033[0m", 179);
		for (int j = 0; j < HEIGHT; j++) {

			if (board[i][j] == (HEIGHT * WIDTH) + 1)printf("\033[91m%c%c\033[0m", 222, 221);
			else if (board[i][j] == 0)printf("  ");
			else printf("\033[93m%c%c\033[0m", 219, 219);
		}
		printf("\033[96m %c \033[0m", 179);
		printf("\n");
	}
	printf("\033[96m%c\033[0m", 192);
	for (int i = 0; i < HEIGHT * 2 + 2; i++)printf("\033[96m%c\033[0m", 196);
	printf("\033[96m%c\n\033[0m", 217);
}
void delay(int ms) {
	clock_t start = clock();
	while (clock() < start + ms - speed);
}

int main(){
	srand(time(NULL));
    char ch = 'd';
	int board[WIDTH][HEIGHT];
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			board[i][j] = 0;
	board[0][0] = 1;
	board[0][1] = 2;
	board[0][2] = 3;
	dropApple(board);
	while (true){
		if (_kbhit()) {
			ch = _getch();
		}
		update(board, ch);
		print(board);
		delay(500);
	}
    return 0;
}