#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

//1. 상단에서 블럭이 하단으로 내려온다.
//2. 도형은 총 7개가 있다.
//3. 특정 키를 눌렀을 때 도형이 회전한다.(4가지 방향으로 회전)
//4. 바닥 또는 도형에 닿으면 다음 도형으로 넘어간다.
//5. 도형을 맞추어 일자가 되면 제거되고 나머지 블럭은 아래로 내려온다.
//출처: https://eskeptor.tistory.com/191 [Hello World:티스토리]


//constexpr int WIN_WIDTH = 70;
//constexpr int WIN_HEIGHT = 60;

//constexpr int MAP_WIDTH = 12;
//constexpr int MAP_HEIGHT = 22;
constexpr int BLOCK_WIDTH = 4;
constexpr int BLOCK_HEIGHT = 4;
//constexpr int START_POS_X = 4;
//constexpr int START_POS_Y = 1;

enum eKeyCode
{
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_SPACE = 32,
    KEY_R = 114,
};

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

int* g_pCurBlock = nullptr;

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
    { }
};

stConsole g_console;

void InitGame(bool bInitConsole = true)
{
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
            break;
        case eKeyCode::KEY_DOWN:
            break;
        case eKeyCode::KEY_LEFT:
            break;
        case eKeyCode::KEY_RIGHT:
            break;
        case eKeyCode::KEY_SPACE:
            break;
        case eKeyCode::KEY_R:
            break;
        default:
            break;
        }
    }
}

void CalcPlayer()
{

}

void CheckBottom()
{

}

void Render(int a, int b)
{

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

void DestroyGame()
{
    if (g_console.hBuffer[0] != nullptr)
    {
        CloseHandle(g_console.hBuffer[0]);
    }

    if(g_console.hBuffer[1] != nullptr)
    {
        CloseHandle(g_console.hBuffer[1]);
    }
}

int main()
{
    InitGame();         // 게임 초기화 (게임 설정 및 콘솔 설정)

    /*char chBuf[256] = { 0, };
    COORD coord{ 0,0 };
    DWORD dw = 0;*/

    int nCurBlock[BLOCK_WIDTH * BLOCK_HEIGHT] = { 0, };
    int nMemSize = sizeof(int) * BLOCK_HEIGHT * BLOCK_WIDTH;
    memcpy_s(nCurBlock, nMemSize, BLOCKS[1], nMemSize);

    printf("");

    for (int nRot = 0; nRot < 1; ++nRot)
    {
        int nTemps[BLOCK_WIDTH * BLOCK_HEIGHT] = { 0, };

        for (int nY = 0; nY < BLOCK_HEIGHT; ++nY)
        {
            for (int nX = 0; nX < BLOCK_WIDTH; ++nX)
            {
                nTemps[(nX * BLOCK_WIDTH) + (BLOCK_HEIGHT - nY - 1)] = nCurBlock[(nY * BLOCK_HEIGHT) + nX];
            }
        }

        memcpy_s(nCurBlock, nMemSize, nTemps, nMemSize);
    }

    printf("");

    while (true)
    {
        // Flickering Test 출력
        /*memset(chBuf, 0, sizeof(chBuf));
        int nLen = sprintf_s(chBuf, sizeof(chBuf), "Flickering Test");
        SetConsoleCursorPosition(g_console.hBuffer[g_console.nCurBuffer], coord);
        WriteFile(g_console.hBuffer[g_console.nCurBuffer], chBuf, nLen, &dw, NULL);*/

        InputKey();     // 키 입력
        //CalcPlayer();   // 플레이어(도형)의 위치 계산

        //CheckBottom();  // 플레이어가 바닥 또는 도형에 닿았는지 확인
        //Render(3, 1);       // 플레이어 및 도형 그리기

        ClearScreen();  // 화면 클리어
        BufferFlip();   // 화면 버퍼 전환 (Double Buffer) 
        Sleep(1);
    }
    
    DestroyGame();      // 게임 제거 (메모리 해제)

    return 0;
}