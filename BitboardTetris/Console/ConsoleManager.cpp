#include "ConsoleManager.h"
#include <iostream>

ConsoleManager::ConsoleManager()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HideCursor();
}

void ConsoleManager::gotoxy(int x, int y)
{
	COORD pos{ (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hConsole, pos);
}

void ConsoleManager::HideCursor()
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hConsole, &CursorInfo);
	CursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &CursorInfo);
}

void ConsoleManager::SleepFrame(int milliseconds)
{
	//@TODO if need it
}

void ConsoleManager::SwapBuffer()
{
	//@TODO if need it
}

void ConsoleManager::PrintText(int x, int y, const std::string& text, WORD color)
{
	gotoxy(x, y);
	SetTextColor(color);
	std::cout << text;
	std::cin.get();
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

void ConsoleManager::ClearArea(int x, int y, int width, int height)
{
	COORD startPos = { (SHORT)x, (SHORT)y };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD written;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	for (int row = 0; row < height; ++row)
	{
		COORD pos = { (SHORT)x, (SHORT)(y + row) };
		FillConsoleOutputCharacter(hConsole, ' ', width, pos, &written);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, width, pos, &written);
	}

	SetConsoleCursorPosition(hConsole, startPos);
}

void ConsoleManager::SetConsoleSize(int width, int height)
{
	COORD bufferSize = { (SHORT)width, (SHORT)height };
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	SMALL_RECT windowSize = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void ConsoleManager::SetTextColor(WORD color)
{
	SetConsoleTextAttribute(hConsole, color);
}
