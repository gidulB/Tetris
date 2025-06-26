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

    // 블록 초기화 (타입 및 기본 좌표 세팅)
    void Initialize(BlockType Type);

    // 블록 회전
    void Rotate();
    void RotateCounterClockwise(); // 필요하면 추가

    // 블록 이동
    void Move(int dx, int dy);

    // 블록을 새로운 타입으로 리셋
    void Reset(BlockType Type);

    // 현재 블록 셀 좌표 가져오기 (맵과 충돌 검사 시 사용)
    std::vector<std::pair<int, int>> GetBlockCells() const;

    // 블록 이동/회전 가능 여부 체크 (맵 필요)
    bool CanMove(int dx, int dy, const std::vector<std::vector<int>>& Map) const;
    bool CanRotate(const std::vector<std::vector<int>>& Map) const;

    // 블록 하드 드랍
    void HardDrop(const std::vector<std::vector<int>>& Map);

    // 현재 블록 타입, 위치 정보
    BlockType GetType() const { return Type; }
    std::pair<int, int> GetPosition() const { return { PosX, PosY }; }
    void SetPosition(int x, int y) { PosX = x; PosY = y; }

private:
    // 회전 상태 (0 ~ 3)
    int Rotation = 0;

    // 블록의 타입 (I, O, T, S, Z, J, L)
    BlockType Type = BlockType::None;

    // 블록의 현재 위치 (맵 기준 좌측 상단 좌표)
    int PosX = 0;
    int PosY = 0;

    // 블록의 상대 좌표 모양 저장 (회전 상태별로)
    std::vector<std::vector<std::pair<int, int>>> ShapeData;

    BlockType eBlock = BlockType::None;
};
