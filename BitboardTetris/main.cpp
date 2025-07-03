#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Player.h"

using namespace std;

//1. 상단에서 블럭이 하단으로 내려온다.
//2. 도형은 총 7개가 있다.
//3. 특정 키를 눌렀을 때 도형이 회전한다.(4가지 방향으로 회전)
//4. 바닥 또는 도형에 닿으면 다음 도형으로 넘어간다.
//5. 도형을 맞추어 일자가 되면 제거되고 나머지 블럭은 아래로 내려온다.
//출처: https://eskeptor.tistory.com/191 [Hello World:티스토리]


//constexpr int WIN_WIDTH = 70;
//constexpr int WIN_HEIGHT = 60;

constexpr int MAP_WIDTH = 12;
constexpr int MAP_HEIGHT = 22;
constexpr int BLOCK_WIDTH = 4;
constexpr int BLOCK_HEIGHT = 4;
constexpr int START_POS_X = 4;
constexpr int START_POS_Y = 1;

enum eKeyCode
{
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_SPACE = 32,
    KEY_R = 114,
};

struct stRect
{
    int nWidth;
    int nHeight;
};

struct stConsole
{
    HANDLE hConsole;
    stRect rtConsole;
    HANDLE hBuffer[2];
    int nCurBuffer;

    stConsole()
        : hConsole(nullptr), hBuffer{ nullptr, }, nCurBuffer(0)
    {
    }
};

const int ORIGIN_MAP[MAP_HEIGHT][MAP_WIDTH] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,0,0,0,0,0,0,0,0,0,0,1,},
    {1,1,1,1,1,1,1,1,1,1,1,1,},
};

const char BLOCK_TYPES[][4] =
{
    "  ",  // 빈 공간
    "▣",  // 프레임
    "□"    // 블록
};

// Map Data
int g_nArrMap[MAP_HEIGHT][MAP_WIDTH] = { 0, };

// Map Data (Backup Data)
//int g_nArrMapBackup[MAP_HEIGHT][MAP_WIDTH] = { 0, };

const int BLOCKS[][BLOCK_WIDTH * BLOCK_HEIGHT] =
{
    { 0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0 },	// I
    { 0,0,0,0,0,0,2,0,0,0,2,0,0,2,2,0 },	// J
    { 0,0,0,0,0,2,0,0,0,2,0,0,0,2,2,0 },	// L
    { 0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0 },	// O
    { 0,0,0,0,0,2,0,0,0,2,2,0,0,0,2,0 },	// S
    { 0,0,0,0,0,2,0,0,2,2,2,0,0,0,0,0 },	// T
    { 0,0,0,0,0,0,2,0,0,2,2,0,0,2,0,0 },	// Z
};

// Player Data
CPlayer g_player;
// Previous Player Data
CPlayer g_prevPlayerData;
// Block Pointer
int* g_pCurBlock = nullptr;
// Console Data
stConsole g_console;

void InitGame(bool bInitConsole = true)
{
    // 플레이어(블럭) 데이터 초기화
    {
        // START_POS_X = 4
        // START_POS_Y = 1
        g_player.SetPosition(START_POS_X, START_POS_Y);
        g_player.SetXPositionRange(-1, MAP_WIDTH);
        g_player.SetYPositionRange(0, MAP_WIDTH);
        g_player.SetBlock(1);
        g_player.SetDirection(CPlayer::eDirection::Dir0);
        g_player.SetGameScore(0);
        g_player.SetGameOver(false);

        g_prevPlayerData = g_player;
    }
    
    // Initialize Console Data
    if (bInitConsole)
    {
        g_console.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        g_console.nCurBuffer = 0;

        // 콘솔 관련 설정
        CONSOLE_CURSOR_INFO consoleCursor{ 1, FALSE }; // 콘솔 커서 깜빡이 제거
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo{ 0, };
        GetConsoleScreenBufferInfo(g_console.hConsole, &consoleInfo);
        consoleInfo.dwSize.X = 40;  // 콘솔의 Width
        consoleInfo.dwSize.Y = 30;  // 콘솔의 Height

        // 콘솔의 크기를 다시 계산 (나중에 그림 그릴 때 다시 사용)
        g_console.rtConsole.nWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left;
        g_console.rtConsole.nHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top;

        // 콘솔의 첫번째 화면 버퍼 생성
        g_console.hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleScreenBufferSize(g_console.hBuffer[0], consoleInfo.dwSize);   // 화면 버퍼 크기 설정
        SetConsoleWindowInfo(g_console.hConsole, TRUE, &consoleInfo.srWindow);  // 콘솔 설정
        SetConsoleCursorInfo(g_console.hConsole, &consoleCursor);               // 콘솔의 커서 설정 

        // 콘솔의 두번째 화면 버퍼 생성
        g_console.hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleScreenBufferSize(g_console.hBuffer[0], consoleInfo.dwSize);   
        SetConsoleWindowInfo(g_console.hConsole, TRUE, &consoleInfo.srWindow);  
        SetConsoleCursorInfo(g_console.hConsole, &consoleCursor);          
    }

    // 맵 데이터 초기화
    {
        int nMapSize = sizeof(int) * MAP_WIDTH * MAP_HEIGHT;
        memcpy_s(g_nArrMap, nMapSize, ORIGIN_MAP, nMapSize);
    }
}

void InputKey()
{
    int nKey = 0;

    if (_kbhit() > 0)
    {
        nKey = _getch();

        switch (nKey)
        {
        case eKeyCode::KEY_UP:
        {
            // 블럭 바로 내리기에 사용
            break;
        }
        case eKeyCode::KEY_DOWN:
        {
            // 아래로 1칸 이동 (Y좌표로 1증가)
            g_player.AddPosition(0, 1);
            break;
        }
        case eKeyCode::KEY_LEFT:
        {
            g_player.AddPosition(-1, 0);
            break;
        }
        case eKeyCode::KEY_RIGHT:
        {
            g_player.AddPosition(1, 0);
            break;
        }
        case eKeyCode::KEY_SPACE:
        {
            // 나중에 블럭 회전에 사용
            break;
        }
        case eKeyCode::KEY_R:
        {
            // 나중에 초기화에 사용
            break;
        }
        default:
            break;
        }
    }
}

void CheckBottom()
{

}

/**
@brief		Rendering function
@param		nXOffset	X Offset (그림을 그릴 때 왼쪽에서부터)
@param		nYOffset	Y Offset (그림을 그릴 때 위쪽에서부터)
@return
*/
void Render(int nXOffset = 0, int nYOffset = 0)
{
    COORD coord = { 0, };
    int nXAdd = 0;
    DWORD dw = 0;

    for (int nY = 0; nY < MAP_HEIGHT; ++nY)
    {
        nXAdd = 0;
        for (int nX = 0; nX < MAP_WIDTH; ++nX)
        {
            coord.X = nXAdd + nXOffset;
            coord.Y = nY + nYOffset;

            SetConsoleCursorPosition(g_console.hBuffer[g_console.nCurBuffer], coord);
            WriteFile(g_console.hBuffer[g_console.nCurBuffer], BLOCK_TYPES[g_nArrMap[nY][nX]], sizeof(BLOCK_TYPES[g_nArrMap[nY][nX]]), &dw, NULL);

            nXAdd += 1;

            // 폰트: 굴림체일 경우
            /*if (g_nArrMap[nY][nX] == 0)
            {
                nXAdd += 1;
            }*/
        }
    }
}

void ClearScreen()
{
    COORD pos{ 0, };
    DWORD dwWritten = 0;
    unsigned size = g_console.rtConsole.nWidth * g_console.rtConsole.nHeight;

    // 콘솔 화면 전체를 띄어쓰기를 넣어 빈 화면처럼 만듭니다.
    FillConsoleOutputCharacter(g_console.hConsole, ' ', size, pos, &dwWritten);
    SetConsoleCursorPosition(g_console.hConsole, pos);
}

void BufferFlip()
{
    // 화면 버퍼 설정
    SetConsoleActiveScreenBuffer(g_console.hBuffer[g_console.nCurBuffer]);
    // 화면 버퍼 인덱스를 교체
    g_console.nCurBuffer = g_console.nCurBuffer ? 0 : 1;
}

/**
@brief		Funtion that get rotate block data
@param		nBlockIdx		Block Index
@param		eDir			Rotate Direction
@return		Block
*/
int* GetRotateBlock(int nBlockIdx, CPlayer::eDirection eDir)
{
    // 이전 블럭의 데이터가 있다면 제거
    if (g_pCurBlock != nullptr)
    {
        delete[] g_pCurBlock;
        g_pCurBlock = nullptr;
    }

    // 새로운 블럭 할당
    g_pCurBlock = new int[BLOCK_HEIGHT * BLOCK_WIDTH];
    int nMemSize = sizeof(int) * BLOCK_HEIGHT * BLOCK_WIDTH;
    memcpy_s(g_pCurBlock, nMemSize, BLOCKS[nBlockIdx], nMemSize);

    // 블럭 회전
    for (int nRot = 0; nRot < (int)eDir; ++nRot)
    {
        int nTemps[BLOCK_HEIGHT * BLOCK_WIDTH] = { 0, };

        for (int nY = 0; nY < BLOCK_HEIGHT; ++nY)
        {
            for (int nX = 0; nX < BLOCK_WIDTH; ++nX)
            {
                nTemps[(nX * BLOCK_WIDTH) + (BLOCK_HEIGHT - nY - 1)] = g_pCurBlock[(nY * BLOCK_HEIGHT) + nX];
            }
        }

        memcpy_s(g_pCurBlock, nMemSize, nTemps, nMemSize);
    }

    return g_pCurBlock;
}

void DestroyGame()
{
    if (g_pCurBlock != nullptr)
    {
        delete[] g_pCurBlock;
        g_pCurBlock = nullptr;
    }

    if (g_console.hBuffer[0] != nullptr)
    {
        CloseHandle(g_console.hBuffer[0]);
    }

    if(g_console.hBuffer[1] != nullptr)
    {
        CloseHandle(g_console.hBuffer[1]);
    }
}

/**
@brief        Function that puts blocks into a map to match the player's position.
@param
@return
*/
void CalcPlayer()
{
    // 현재 플레이어(블럭) 위치를 받아온다.
    COORD playerCursor = g_player.GetCursor();

    // 이전 위치의 블럭 코드 제거
    if (g_prevPlayerData != g_player)
    {
        int* pBlock = GetRotateBlock(g_prevPlayerData.GetBlock(), g_prevPlayerData.GetDirection());
        COORD sprevCursor = g_prevPlayerData.GetCursor();

        for (int nY = 0; nY < BLOCK_HEIGHT; ++nY)
        {
            for (int nX = 0; nX < BLOCK_WIDTH; ++nX)
            {
                // 이전 위치의 블럭이 위치한 좌표의 데이터를 지워줌
                if (pBlock[(nY * BLOCK_HEIGHT) + nX] &&
                    pBlock[(nY * BLOCK_HEIGHT) + nX] == g_nArrMap[sprevCursor.Y + nY][sprevCursor.X + nX])
                {
                    g_nArrMap[sprevCursor.Y + nY][sprevCursor.X + nX] = 0;
                }
            }
        }

        // 현재 플레이어(블럭)의 정보를 이전 정보에 기록
        g_prevPlayerData = g_player;
    }

    // 현재 블럭의 방향에 따른 모양을 받아온다.
    int* pBlock = GetRotateBlock(g_player.GetBlock(), g_player.GetDirection());
    for (int nY = 0; nY < BLOCK_HEIGHT; ++nY)
    {
        for (int nX = 0; nX < BLOCK_WIDTH; ++nX)
        {
            if (pBlock[(nY * BLOCK_HEIGHT) + nX])
            {
                g_nArrMap[playerCursor.Y + nY][playerCursor.X + nX] = pBlock[nY * BLOCK_HEIGHT + nX];
            }
        }
    }
}

int main()
{
    InitGame();         // 게임 초기화 (게임 설정 및 콘솔 설정)

    while (true)
    {       
        InputKey();     // 키 입력
        CalcPlayer();   // 플레이어(도형)의 위치 계산

        //CheckBottom();  // 플레이어가 바닥 또는 도형에 닿았는지 확인
        Render(3, 1);       // 플레이어 및 도형 그리기

        ClearScreen();  // 화면 클리어
        BufferFlip();   // 화면 버퍼 전환 (Double Buffer) 
        Sleep(1);
    }
    
    DestroyGame();      // 게임 제거 (메모리 해제)

    return 0;
}