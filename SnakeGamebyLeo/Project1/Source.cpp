////////////////////////////////////////////////////////////////
//------------------------------------------------------------//
//-               Snake Game - Using Console Log             -//
//-							     -//
//-							     -//
//-   Created By : Leo HoGyeong Cho			     -//
//-   Last Edit  : April 6th, 2018			     -//
//-							     -//
//-							     -//
//------------------------------------------------------------//
////////////////////////////////////////////////////////////////
// ## Things to improve ##
// - bug while wall switching simultaneously
// - fruits appearing at tails or snakes's head
// - possible instructions on the bottom part(suggested font, keyboard input etc)
// - compatibility to arrow keys 
// - better walls, snake, tails, fruits ( search on web?)
// - replay button after win or gameover
// - difficulty settings? (making game faster, less score for beginner etc)


#include <iostream>
#include <conio.h>
#include <ctime>		// for time()
#include <cstdlib>
#include <windows.h>	// Sleep(), sytem()
#include <iomanip>

using namespace std;

bool gameover, win;

const int width = 30;
const int height = 20;
int score = 0;
int x, y, fruitX, fruitY;
int tailX[100], tailY[100];
int tailnum = 1;
bool Yup, Ydown, Xleft, Xright;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN, TEST };
eDirection dir;
eDirection test;
double gamespeed;

void setup() {

	gamespeed = 80;
	srand(time(0));

	gameover = false;
	win = false;

	x = width / 2;
	y = height / 2;
	fruitX = (rand() % width) + 1;
	fruitY = (rand() % height) + 1;

	dir = STOP;


	// four directional boolean variables to control snake's moverment
	// currently using it to make snake cant go to opposite direction instantly
	Yup = true;
	Ydown = true;
	Xleft = true;
	Xright = true;

}

void draw() {

	system("cls");

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (i == 0 || i == width - 1) {
				cout << "#";
			}
			else if (j == y && i == x) {
				cout << "O";
			}
			else if (i == fruitX && j == fruitY) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < tailnum; k++) {
					if (tailX[k] == i && tailY[k] == j) {
						cout << "o";
						print = true;
					}
				}
				if(!print) cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";

	cout << endl << "Score : " << score << endl;
	cout << setprecision(0) << fixed;
	cout << "Gamespeed : " << (100 - gamespeed) << endl;
	cout << "F = ( " << setw(2) << fruitX << ", " << setw(2) << fruitY << " )" << setw(14) <<       "Created By" << endl;
	cout << "O = ( " << setw(2) << x << ", " << setw(2) << y << " )" << setw(20) <<			  "HoGyeong Leo Cho";
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w' :
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameover = true;
			break;
		case 't' :
			test = TEST;
			break;
		}
	}
}

void logic() {
	
	// It is absolutely important to remember that the sequence of logic is crucial here
	// certain things has to be excuted faster than other statements

	switch (dir) {
	case UP:
		if (Yup == true) {
			y--;
			Yup = true;
			Ydown = false;
			Xleft = true;
			Xright = true;
		}
		else {
			y++;
		}
		break;
	case DOWN:
		if (Ydown == true) {
			y++;
			Yup = false;
			Ydown = true;
			Xleft = true;
			Xright = true;
		}
		else {
			y--;
		}
		break;
	case LEFT:
		if (Xleft == true) {
			x--;
			Xleft = true;
			Xright = false;
			Yup = true;
			Ydown = true;
		}
		else {
			x++;
		}
		break;
	case RIGHT:
		if( Xright == true){
			x++;
			Xleft = false;
			Xright = true;
			Yup = true;
			Ydown = true;
		}
		else {
			x--;
		}
		break;
	}

	//Wall-riding sort of incomplete at this moment June 5 2018
	if (x == width - 1) {
		x = 1;
	}
	if (x == 0) {
		x = width - 2;
	}

	if (y == height) {
		y = 0;
	}
	if (y < 0) {
		y = height;
	}

	
	// When Snake Head contacts Fruity
	if (test == TEST || x == fruitX && y == fruitY) {
		fruitX = rand() % (width - 2) + 1;
		fruitY = rand() % (height);
		if (gamespeed > 0) gamespeed -= 1;
		tailnum++;
		score += 10;
	}

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < tailnum; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	for (int i = 2; i < tailnum; i++) {
		if (x == tailX[i] && y == tailY[i]) gameover = true;
	}

	if (score == 1000) win = true;
}

void gameoverscreen() {

	bool gameover = false;
	system("cls");

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int j = 0; j < height - 1; j++) {
		for (int i = 0; i < width; i++) {
			if (j == 10 && !gameover) {
				cout << "#         GAME  OVER         #" << endl;
				cout << "#                            #";
				gameover = true;

			}
			else if (i == 0 || i == width - 1 && !gameover) {
				cout << "#";
			} 
			else if(!gameover){
				cout << " ";
			}			
		}
		gameover = false;
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";

	cout << endl << "Score : " << score << endl;
	cout << setprecision(0) << fixed;
	cout << "Gamespeed : " << (100 - gamespeed) << endl;
	cout << "F = ( " << setw(2) << fruitX << ", " << setw(2) << fruitY << " )" << setw(14) << "Created By" << endl;
	cout << "O = ( " << setw(2) << x << ", " << setw(2) << y << " )" << setw(20) << "HoGyeong Leo Cho";
	
}

void winscreen() {
	bool gameover = false;
	system("cls");

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int j = 0; j < height - 1; j++) {
		for (int i = 0; i < width; i++) {
			if (j == 10 && !gameover) {
				cout << "#          You  Won!         #" << endl;
				cout << "#  Thank You for Playing :D  #";
				gameover = true;

			}
			else if (i == 0 || i == width - 1 && !gameover) {
				cout << "#";
			}
			else if (!gameover) {
				cout << " ";
			}
		}
		gameover = false;
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";

	cout << endl << "Score : " << score << endl;
	cout << setprecision(0) << fixed;
	cout << "Gamespeed : " << (100 - gamespeed) << endl;
	cout << "F = ( " << setw(2) << fruitX << ", " << setw(2) << fruitY << " )" << setw(14) << "Created By" << endl;
	cout << "O = ( " << setw(2) << x << ", " << setw(2) << y << " )" << setw(20) << "HoGyeong Leo Cho";
}

int main() {

	setup();

	while (!gameover && !win) {
		draw();
		input();
		logic();
		// dir = STOP;
		Sleep(gamespeed);
	}

	if (gameover) gameoverscreen();
	if (win) winscreen();

	Sleep(5000);

}
