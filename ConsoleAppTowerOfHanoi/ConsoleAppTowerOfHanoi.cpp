/*
	Ten: ...
	Lop: ...
	Project: ....
	.....
*/
#include <iostream>
#include <conio.h> 
#include <string>
#include <algorithm>
#include <windows.h> 
#include <cstdlib>
#include <fstream> 
#include <time.h>       /* time */
#include "MyWindows.h"; 
#include "Stack.h"

using namespace std;

#define WIDTH  100
#define HEIGHT 30

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15

int row = 1;
void draw(MyWindows console, Stack* stack)
{
	/*
	          1111
	       2222222222
	    33333333333333333
	 w ---------------------       --------------------------    -------------------------
	left      x1                              x2                           x3
	*/
	int left = 5;
	int w = (WIDTH - 4 * left) / 3;
	int x[3];
	x[0] = left + w / 2;
	x[1] = x[0] + w + left;
	x[2] = x[1] + w + left;
	int lastRow = HEIGHT - 4;

	for (int i = 0; i < w; i++)
	{
		console.Write(L"─", x[0] - (w / 2) + i, lastRow, BLUE, WHITE);
		console.Write(L"─", x[1] - (w / 2) + i, lastRow, BLUE, WHITE);
		console.Write(L"─", x[2] - (w / 2) + i, lastRow, BLUE, WHITE); 
	}
	for (int i = 0; i < 3; i++)
	{
		MyWindows win(x[i] - w / 2, 2, w, HEIGHT - 6, BLUE, BLUE);
		win.clearConsole();
		win.drawFrame(); 
		for (int j = 1; j < 15; j++)
		{
			console.Write(L"│", x[i], lastRow - j, BLUE, WHITE);
		}

		Stack temp;
		int disk;
		int stackLength = stack[i].getLength();
		while (stack[i].pop(&disk)) {
			int diskWidth = (disk * 4) + 1;
			MyWindows win(x[i] - diskWidth / 2, lastRow - stackLength * 2, diskWidth, 2, disk + 3, WHITE);
			win.clearConsole();
			win.drawFrame();
			stackLength--;
			temp.push(disk);
		}
		while (temp.pop(&disk)) {
			// push la.i co^.t thie.t
			stack[i].push(disk);
		} 
	}
	Sleep(100);
}
void towerOfHanoi(MyWindows console, Stack* stack, int n, int source, int target, int temp)  // N from source to target (du`ng temp phu.)
{
	if (n == 1)
	{
		//cout << "Move disk from " << source << " to " << target << endl;
		/*
		1
		2
		3
		*/
		int disk;
		if (stack[source - 1].pop(&disk))
		{
			if (stack[target - 1].push(disk))
			{
				//console.Write("Move disk #" + to_string(disk) + " from rod " + to_string(source) + " to rod " + to_string(target), 2, row++, BLUE, WHITE);
				draw(console, stack);
			}
			else 
			{
				console.Write("Push Error", 2, row++, BLUE, WHITE);
				return;
			}
		}
		else {
			console.Write("Pop Error", 2, row++, BLUE, WHITE);
			return;
		}
		return;
	}
	towerOfHanoi(console, stack, n - 1, source, temp, target);
	int disk;
	if (stack[source - 1].pop(&disk)) 
	{
		if (stack[target - 1].push(disk))
		{
			//console.Write("Move disk #" + to_string(disk) + " from rod " + to_string(source) + " to  rod " + to_string(target), 2, row++, BLUE, WHITE);
			draw(console, stack);
		}
		else
		{
			console.Write("Push Error", 2, row++, BLUE, WHITE);
			return;
		}
	}
	else
	{
		console.Write("Pop Error", 2, row++, BLUE, WHITE);
		return;
	}
	towerOfHanoi(console, stack, n - 1, temp, target, source);
}
int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	MyWindows console(0, 0, WIDTH, HEIGHT, BLUE, WHITE);
	console.clearConsole();
	console.drawFrame();
	console.Write(" Tower of Hanoi ", 2, 0, BLUE, WHITE);

	int n = 5;
	Stack stack[3];  
	for (int i = n; i >= 1; i--)
	{
		stack[0].push(i); // index 0 = cot 1: push vao cot 1: 3 2 1
	}
	draw(console, stack);
	towerOfHanoi(console, stack, n, 1, 3, 2);
	console.Write("DONE", WIDTH / 2 - 3, HEIGHT / 3, BLUE, WHITE);

	//cout << endl << endl;
	//cout << "Nhan bat ky phim nao de ket thuc chuong trinh";
	char ch = _getch();
}
