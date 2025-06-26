#include "ConsoleManager.h"
#include <iostream>

ConsoleManager::ConsoleManager()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == nullptr || hConsole == INVALID_HANDLE_VALUE)
	{
		std::cerr << "ÄÜ¼Ö ÇÚµé È¹µæ ½ÇÆÐ!" << std::endl;
		exit(1);
	}

	HideCursor();
}

ConsoleManager* ConsoleManager::GetInstance()
{
	static ConsoleManager instance; 
	return &instance;
}

void ConsoleManager::gotoxy(int X, int Y)
{
	COORD pos{ (SHORT)X, (SHORT)Y };
	SetConsoleCursorPosition(hConsole, pos);
}

void ConsoleManager::HideCursor()
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hConsole, &CursorInfo);
	CursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &CursorInfo);
}

void ConsoleManager::SleepFrame(int Milliseconds)
{
	Sleep(Milliseconds);
}

void ConsoleManager::SwapBuffer()
{
	//@TODO if need it
}

void ConsoleManager::PrintText(int X, int Y, const std::string& Text, WORD Color)
{
	gotoxy(X, Y);
	SetTextColor(Color);
	std::cout << Text;
}

void ConsoleManager::Clear()
{
	COORD topLeft = { 0, 0 };
	DWORD written, length;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	length = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hConsole, ' ', length, topLeft, &written);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(hConsole, topLeft);
}

void ConsoleManager::ClearArea(int X, int Y, int Width, int Height)
{
	COORD startPos = { (SHORT)X, (SHORT)Y };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD written;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	for (int row = 0; row < Height; ++row)
	{
		COORD pos = { (SHORT)X, (SHORT)(Y + row) };
		FillConsoleOutputCharacter(hConsole, ' ', Width, pos, &written);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, Width, pos, &written);
	}

	SetConsoleCursorPosition(hConsole, startPos);
}

void ConsoleManager::SetConsoleSize(int Width, int Height)
{
	COORD bufferSize = { (SHORT)Width, (SHORT)Height };
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	SMALL_RECT windowSize = { 0, 0, (SHORT)(Width - 1), (SHORT)(Height - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void ConsoleManager::SetTextColor(WORD color)
{
	SetConsoleTextAttribute(hConsole, color);
}
