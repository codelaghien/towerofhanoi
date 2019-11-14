#pragma once
using namespace std;

class MyWindows
{
private:
	int _Left = 0;
	int _Top = 0;
	int _Width = 0;
	int _Height = 0;
	int _BackgroundColor = 0;
	int _ForegroundColor = 7;
	/*
		Console.WriteLine("Hello World ! ┌───┐ ");
		Console.WriteLine("Hello World ! │   │ ");
		Console.WriteLine("Hello World ! │   │ ");
		Console.WriteLine("Hello World ! └───┘ ");
	*/
	wstring _frame = L"┌─┐│└┘";

public:
	MyWindows(int left, int top, int width, int height, int backgroundColor = 0, int foregroundColor = 7);
	~MyWindows();

	void gotoXY(int x, int y);
	void clearConsole();
	void Write(string st, int x, int y, int backgroundColor = 0, int foregroundColor = 7);
	void Write(wstring st, int x, int y, int backgroundColor = 0, int foregroundColor = 7);
	void drawFrame();
private:
	wstring ConvertToWString(string st);
};
