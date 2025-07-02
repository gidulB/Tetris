#include "BlockGenerator.h"
#include "Block.h"

int BlockGenerator::GenerateBlock(int blockType, int rotation, int color, int shape, 
	int size, int position, int orientation)
{
	int block = (blockType << 28) | (rotation << 24) | (color << 20) | (shape << 16) |
		(size << 12) | (position << 8) | (orientation << 4);

	return block;
}

int BlockGenerator::GetBlockType(int block)
{
	int blockType = (block & BLOCK_TYPE_MASK) >> 28;
	return blockType;
}

int BlockGenerator::GetBlockRotation(int block)
{
	int blockRotation = (block & BLOCK_ROTATION_MASK) >> 24;
	return blockRotation;
}

int BlockGenerator::GetBlockColor(int block)
{
	int blockColor = (block & BLOCK_COLOR_MASK) >> 20;
	return blockColor;
}

int BlockGenerator::GetBlockShape(int block)
{
	int blockShape = (block & BLOCK_SHAPE_MASK) >> 16;
	return blockShape;
}

int BlockGenerator::GetBlockSize(int block)
{
	int blockSize = (block & BLOCK_SIZE_MASK) >> 12;
	return blockSize;
}

int BlockGenerator::GetBlockPosition(int block)
{
	int blockPosition = (block & BLOCK_POSITION_MASK) >> 8;
	return blockPosition;
}

int BlockGenerator::GetBlockOrientation(int block)
{
	int blockOrientation = (block & BLOCK_ORIENTATION_MASK) >> 4;
	return blockOrientation;
}

int BlockGenerator::GenerateBlockInternal(int blockType, int rotation, int color, int shape, int size, int position, int orientation)
{
	return 0;
}

int BlockGenerator::ExtractBlockProperty(int block, int propertyMask, int propertyShift)
{
	static const int BlockProperty = (block & propertyMask) >> propertyShift;
	return BlockProperty;
}

int BlockGenerator::CreateBlock(int blockType, int rotation, int color, int shape, int size, int position, int orientation)
{
	return 0;
}

int BlockGenerator::CombineBlockProperties(int blockType, int rotation, int color, int shape, int size, int position, int orientation)
{
	return 0;
}
