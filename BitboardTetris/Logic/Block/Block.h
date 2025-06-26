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

    // ��� �ʱ�ȭ (Ÿ�� �� �⺻ ��ǥ ����)
    void Initialize(BlockType Type);

    // ��� ȸ��
    void Rotate();
    void RotateCounterClockwise(); // �ʿ��ϸ� �߰�

    // ��� �̵�
    void Move(int dx, int dy);

    // ����� ���ο� Ÿ������ ����
    void Reset(BlockType Type);

    // ���� ��� �� ��ǥ �������� (�ʰ� �浹 �˻� �� ���)
    std::vector<std::pair<int, int>> GetBlockCells() const;

    // ��� �̵�/ȸ�� ���� ���� üũ (�� �ʿ�)
    bool CanMove(int dx, int dy, const std::vector<std::vector<int>>& Map) const;
    bool CanRotate(const std::vector<std::vector<int>>& Map) const;

    // ��� �ϵ� ���
    void HardDrop(const std::vector<std::vector<int>>& Map);

    // ���� ��� Ÿ��, ��ġ ����
    BlockType GetType() const { return Type; }
    std::pair<int, int> GetPosition() const { return { PosX, PosY }; }
    void SetPosition(int x, int y) { PosX = x; PosY = y; }

private:
    // ȸ�� ���� (0 ~ 3)
    int Rotation = 0;

    // ����� Ÿ�� (I, O, T, S, Z, J, L)
    BlockType Type = BlockType::None;

    // ����� ���� ��ġ (�� ���� ���� ��� ��ǥ)
    int PosX = 0;
    int PosY = 0;

    // ����� ��� ��ǥ ��� ���� (ȸ�� ���º���)
    std::vector<std::vector<std::pair<int, int>>> ShapeData;

    BlockType eBlock = BlockType::None;
};
