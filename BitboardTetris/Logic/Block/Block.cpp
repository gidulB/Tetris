#include "Block.h"

#include "Console/ConsoleManager.h"
#include "Render/RenderManager.h"
#include "Input/InputManager.h"

Block::Block()
{		
	RenderManager* Render = RenderManager::GetInstance();

	switch (eBlock)
	{
	case BlockType::I:
		//Render->DrawString(4, 0, "#");
		break;
	case BlockType::O:
		//Render->DrawString(2, 2, "#");
		break;
	case BlockType::T:
		//Render->DrawString(3, 4, "#");
		break;
	case BlockType::S:
		//Render->DrawString(4, 2, "#");
		break;
	case BlockType::Z:
		//Render->DrawString(2, 4, "#");
		break;
	case BlockType::J:
		//Render->DrawString(3, 2, "#");
		break;
	case BlockType::L:
		//Render->DrawString(2, 3, "#");
		break;
	default:
		break;
	}
}

void Block::Initialize(BlockType Type)
{
	eBlock = Type;

	switch (eBlock)
	{
	case BlockType::I:
		break;
	case BlockType::O:
		break;
	case BlockType::T:
		break;
	case BlockType::S:
		break;
	case BlockType::Z:
		break;
	case BlockType::J:
		break;
	case BlockType::L:
		break;
	default:
		break;
	}
}

void Block::Rotate()
{
}

void Block::RotateCounterClockwise()
{
}

void Block::Move(int dx, int dy)
{	
	PosX += dx;
	PosY += dy;
}

void Block::Reset(BlockType Type)
{
}

std::vector<std::pair<int, int>> Block::GetBlockCells() const
{
	return std::vector<std::pair<int, int>>();
}

bool Block::CanMove(int dx, int dy, const std::vector<std::vector<int>>& Map) const
{
	return false;
}

bool Block::CanRotate(const std::vector<std::vector<int>>& Map) const
{
	return false;
}

void Block::HardDrop(const std::vector<std::vector<int>>& Map)
{
	RenderManager* Render = RenderManager::GetInstance();
	if (!Render) return;

	int Height = Render->GetHeight();
	int Width = Render->GetWidth();

}
