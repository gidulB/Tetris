#pragma once

class BlockGenerator
{
public:
	static int GenerateBlock(int blockType, int rotation, int color, int shape, int size, int position, int orientation);

	static int GetBlockType(int block);
	static int GetBlockRotation(int block);
	static int GetBlockColor(int block);
	static int GetBlockShape(int block);
	static int GetBlockSize(int block);
	static int GetBlockPosition(int block);
	static int GetBlockOrientation(int block);

private:
	static int GenerateBlockInternal(int blockType, int rotation, int color, int shape, int size, int position, int orientation);
	static int ExtractBlockProperty(int block, int propertyMask, int propertyShift);
	static int CreateBlock(int blockType, int rotation, int color, int shape, int size, int position, int orientation);
	static int CombineBlockProperties(int blockType, int rotation, int color, int shape, int size, int position, int orientation);

private:
	static const int BLOCK_TYPE_MASK = 0xF0000000; // Mask for block type
	static const int BLOCK_ROTATION_MASK = 0x0F000000; // Mask for rotation
	static const int BLOCK_COLOR_MASK = 0x00FF0000; // Mask for color
	static const int BLOCK_SHAPE_MASK = 0x0000FF00; // Mask for shape
	static const int BLOCK_SIZE_MASK = 0x000000FF; // Mask for size
	static const int BLOCK_POSITION_MASK = 0x0000000F; // Mask for position
	static const int BLOCK_ORIENTATION_MASK = 0x000000F0; // Mask for orientation
};