#include "Console/ConsoleManager.h"

int main()
{
    ConsoleManager* console = ConsoleManager::GetInstance();
    console->PrintText(10, 5, "<Bitboard Tetris>", (4 << 4 | 7));
    
    return 0;
}