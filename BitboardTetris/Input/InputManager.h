#pragma once
#include <unordered_map>
#include <windows.h>

class InputManager
{
public:
    static InputManager* GetInstance();
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

private:
    InputManager();

public:
    void Update();

    bool IsKeyDown(int Key);      
    bool IsKeyUp(int Key);        
    bool IsKeyPressed(int Key);  
    bool IsKeyHeld(int Key, float HoldTime);

private:
    HANDLE hConsole = nullptr;

    std::unordered_map<int, bool> CurrentKeys;  
    std::unordered_map<int, bool> PreviousKeys;
    std::unordered_map<int, float> KeyHoldStartTimes;
};