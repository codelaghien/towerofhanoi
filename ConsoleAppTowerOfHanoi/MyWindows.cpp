#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
using namespace std;

#include "MyWindows.h"
MyWindows::MyWindows(int left, int top, int width, int height, int backgroundColor, int foregroundColor)
{
	_Left = left;
	_Top = top;
	_Width = width;
	_Height = height;
	_BackgroundColor = backgroundColor;
	_ForegroundColor = foregroundColor;
}


MyWindows::~MyWindows()
{
}

void MyWindows::drawFrame()
{
	/*
		Console.WriteLine("Hello World ! ┌───┐ ");
		Console.WriteLine("Hello World ! │   │ ");
		Console.WriteLine("Hello World ! │   │ ");
		Console.WriteLine("Hello World ! └───┘ ");
		wstring _frame = L"┌─┐│└┘";
	*/
	Write(_frame.substr(0, 1), 0, 0, _BackgroundColor, _ForegroundColor);
	for (int i = 0; i < _Width - 2; i++)
	{
		Write(_frame.substr(1, 1), 1 + i, 0, _BackgroundColor, _ForegroundColor);
	}
	Write(_frame.substr(2, 1), _Width - 1, 0, _BackgroundColor, _ForegroundColor);

	for (int i = 1; i < _Height - 1; i++)
	{
		Write(_frame.substr(3, 1), 0, i, _BackgroundColor, _ForegroundColor);
		Write(_frame.substr(3, 1), _Width - 1, i, _BackgroundColor, _ForegroundColor);
	}

	Write(_frame.substr(4, 1), 0, _Height - 1, _BackgroundColor, _ForegroundColor);
	for (int i = 0; i < _Width - 2; i++)
	{
		Write(_frame.substr(1, 1), 1 + i, _Height - 1, _BackgroundColor, _ForegroundColor);
	}
	Write(_frame.substr(5, 1), _Width - 1, _Height - 1, _BackgroundColor, _ForegroundColor);

	//Write(L"Hello", (_Width - 5) / 2, (_Height) / 2 - 1, _BackgroundColor, _ForegroundColor);
}

wstring MyWindows::ConvertToWString(string st)
{
	using convert_t = std::codecvt_utf8<wchar_t>;
	wstring_convert<convert_t, wchar_t> strconverter;
	return strconverter.from_bytes(st);
}
void MyWindows::Write(wstring st, int x, int y, int backgroundColor, int foregroundColor) {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int stringlen = st.length();
	const wchar_t* text = st.c_str();
	CHAR_INFO* consoletext = new CHAR_INFO[stringlen];
	COORD a = { stringlen, 1 }, b = { 0, 0 };
	SMALL_RECT c = { _Left + x, _Top + y, _Left + x + stringlen, _Top + y + 1 };
	WORD wColor = ((backgroundColor & 0x0F) << 4) + (foregroundColor & 0x0F);
	for (int i = 0; i < stringlen; i++)
	{
		//consoletext[i].Char.AsciiChar = text[i];
		consoletext[i].Char.UnicodeChar = text[i];
		consoletext[i].Attributes = wColor;
	}
	WriteConsoleOutput(hout, consoletext, a, b, &c);
}
void MyWindows::Write(string st, int x, int y, int backgroundColor, int foregroundColor) {
	Write(ConvertToWString(st), x, y, backgroundColor, foregroundColor);
}

void MyWindows::gotoXY(int x, int y) {
	COORD coord = { _Left + x, _Top + y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MyWindows::clearConsole() {
	for (int row = 1; row < _Height - 1; row++)
	{
		for (int col = 1; col < _Width - 1; col++)
		{
			Write(L" ", col, row, _BackgroundColor, _ForegroundColor);
		}
	}
	/*HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { _Left, _Top };
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		SetConsoleCursorPosition(hStdOut, coord);
	}*/
}

