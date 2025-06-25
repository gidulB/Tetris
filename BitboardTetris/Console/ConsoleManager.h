#pragma once
#include <windows.h>
#include <string>

class ConsoleManager
{
public:
	static ConsoleManager* GetInstance();

	ConsoleManager(const ConsoleManager&) = delete;
	ConsoleManager& operator=(const ConsoleManager&) = delete;

private:
	ConsoleManager();

public:
	void gotoxy(int X, int Y);
	void HideCursor();
	void SleepFrame(int Milliseconds); // Manage Timer/Frame 
	void SwapBuffer(); // if I Extend double Buffer, I'll Use it
	void PrintText(int X, int Y, const std::string& Text, WORD Color);
	void Clear();
	void ClearArea(int X, int Y, int Width, int Height); // Delete Testris Block?

public:
	void SetConsoleSize(int Width, int Height);
	void SetTextColor(WORD Color);

	HANDLE Gethandle() { return hConsole; }

private:
	HANDLE hConsole = nullptr;
};