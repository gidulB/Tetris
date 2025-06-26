#include "RenderManager.h"
#include "Console/ConsoleManager.h"
#include <iostream>

RenderManager* RenderManager::GetInstance()
{
	static RenderManager instance(50, 20);
	return &instance;
}

RenderManager::RenderManager(int Width, int Height)
	: Width(Width), Height(Height)
{
	Console = Console->GetInstance();
	if (!Console) return;

	Buffer.resize(Height, std::vector<char>(Width, ' '));
}

void RenderManager::ClearBuffer()
{
	Console->Clear();

	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			Buffer[y][x] = ' ';
		}
	}
}

void RenderManager::DrawChar(int X, int Y, char Ch)
{
	if (X < 0 || X >= Width || Y < 0 || Y >= Height) return;

	Buffer[Y][X] = Ch;
}

void RenderManager::DrawString(int X, int Y, const std::string& Str)
{
	if (Y < 0 || Y >= Height) return;

	//@TODO 공백 수정 필요

	for (size_t i = 0; i < Str.size(); ++i)
	{
		int DrawX = X + static_cast<int>(i);
		if (DrawX >= 0 && DrawX < Width) 
		{
			Buffer[Y][DrawX] = Str[i];
		}
	}
}

void RenderManager::DrawBorder()
{
	if (Width < 2 || Height < 2) return;

	for (int x = 0; x < Width; ++x)
	{
		Buffer[0][x] = '-';
		Buffer[Height - 1][x] = '-';
	}

	for (int y = 0; y < Height; ++y)
	{
		Buffer[y][0] = '|';
		Buffer[y][Width - 1] = '|';
	}

	Buffer[0][0] = '+';
	Buffer[0][Width - 1] = '+';
	Buffer[Height - 1][0] = '+';
	Buffer[Height - 1][Width - 1] = '+';
}

void RenderManager::Render()
{
	if (!Console) return;
	
	Console->gotoxy(0, 0);

	for (int y = 0; y < Height; ++y)
	{
		std::string row;
		for (int x = 0; x < Width; ++x)
		{
			row += Buffer[y][x];
		}		

		Console->PrintText(0, y, row, 7);
	}
}
