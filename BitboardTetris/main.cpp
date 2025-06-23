#include "Console/ConsoleManager.h"

int main()
{
    ConsoleManager console;
    console.PrintText(10, 5, "<Bitboard Tetris>", (4 << 4 | 7));
    
    return 0;
}