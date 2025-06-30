#pragma once
#include <vector>
#include <utility> // for std::pair

enum class BlockType
{
    I, O, T, S, Z, J, L, None
};

class Block
{
public:
    Block();
    ~Block() = default;

    void Initialize(BlockType Type);

    void Rotate();
    void RotateCounterClockwise(); 

    void Move(int dx, int dy);

    void Reset(BlockType Type);

    std::vector<std::pair<int, int>> GetBlockCells() const;

    bool CanMove(int dx, int dy, const std::vector<std::vector<int>>& Map) const;
    bool CanRotate(const std::vector<std::vector<int>>& Map) const;

    void HardDrop(const std::vector<std::vector<int>>& Map);

    BlockType GetType() const { return Type; }
    std::pair<int, int> GetPosition() const { return { PosX, PosY }; }
    void SetPosition(int x, int y) { PosX = x; PosY = y; }

private:
    // (0 ~ 3)
    int Rotation = 0;

    // (I, O, T, S, Z, J, L)
    BlockType Type = BlockType::None;

    int PosX = 0;
    int PosY = 0;

    std::vector<std::vector<std::pair<int, int>>> ShapeData;

    BlockType eBlock = BlockType::None;
};
