#include <iostream>

#include "Console/ConsoleManager.h"
#include "Render/RenderManager.h"

int main()
{
    ConsoleManager* Console = ConsoleManager::GetInstance();
    Console->SetConsoleSize(50, 20);

    RenderManager* Render = RenderManager::GetInstance();

    while (true)
    {
        Render->ClearBuffer();
        Render->DrawBorder();

        Render->DrawChar(10, 5, '#');
        Render->DrawString(15, 7, "Help Me");

        Render->Render();

        Console->SleepFrame(1000);

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) 
            break;
    }
    
    return 0;
}