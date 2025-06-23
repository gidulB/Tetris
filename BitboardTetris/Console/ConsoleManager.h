#pragma once
#include <windows.h>
#include <string>

class ConsoleManager
{
public:
	ConsoleManager();

	void gotoxy(int x, int y);
	void HideCursor();
	void SleepFrame(int milliseconds); // Manage Timer/Frame 
	void SwapBuffer(); // if I Extend double Buffer, I'll Use it
	void PrintText(int x, int y, const std::string& text, WORD color = 7);
	void Clear();
	void ClearArea(int x, int y, int width, int height); // Delete Testris Block?

public:
	void SetConsoleSize(int width, int height);
	void SetTextColor(WORD color);

	HANDLE Gethandle() { return hConsole; }

private:
	HANDLE hConsole = nullptr;
};