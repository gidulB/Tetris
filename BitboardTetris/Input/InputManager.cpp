#include "InputManager.h"
#include "Console/ConsoleManager.h"
#include <iostream>

InputManager* InputManager::GetInstance()
{
    static InputManager instance;
    return &instance;
}

InputManager::InputManager()
{
    ConsoleManager* Console = ConsoleManager::GetInstance();
    if (!Console) return;

    hConsole = Console->Gethandle();
}

void InputManager::Update()
{
	// Save the previous key states
    PreviousKeys = CurrentKeys;

	// Initialize the current key states
    CurrentKeys.clear();

    DWORD eventsRead = 0;
    INPUT_RECORD inputRecord;

	// Handle any pending input events
    while (PeekConsoleInput(hConsole, &inputRecord, 1, &eventsRead) && eventsRead > 0)
    {
        ReadConsoleInput(hConsole, &inputRecord, 1, &eventsRead);

        if (inputRecord.EventType == KEY_EVENT)
        {
            int KeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;
            bool IsPressed = inputRecord.Event.KeyEvent.bKeyDown;

            CurrentKeys[KeyCode] = IsPressed;

			// If the key is pressed, record the time it was held down
            if (IsPressed)
            {
                if (KeyHoldStartTimes.find(KeyCode) == KeyHoldStartTimes.end())
                {
                    KeyHoldStartTimes[KeyCode] = GetTickCount64();
                }
            }
            else
            {
				// If the key released, remove the hold time record
                KeyHoldStartTimes.erase(KeyCode);
            }
        }
    }
}

bool InputManager::IsKeyDown(int Key)
{
    return CurrentKeys[Key] && !PreviousKeys[Key];
}

bool InputManager::IsKeyUp(int Key)
{
    return !CurrentKeys[Key] && PreviousKeys[Key];
}

bool InputManager::IsKeyPressed(int Key)
{
    return CurrentKeys[Key];
}

bool InputManager::IsKeyHeld(int Key, float HoldTime)
{
    if (CurrentKeys[Key])
    {
        DWORD currentTime = GetTickCount64();
		float heldDuration = (currentTime - KeyHoldStartTimes[Key]) / 1000.0f; // Changed to float for precision

        if (heldDuration >= HoldTime)
            return true;
    }
    else
    {
        KeyHoldStartTimes.erase(Key); // Remove the key if it's not currently pressed
	}
    return false;
}
