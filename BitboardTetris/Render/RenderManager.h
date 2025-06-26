#pragma once
#include <vector>
#include <string>

class RenderManager
{
public:
    static RenderManager* GetInstance();
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;

private:
    RenderManager(int Width, int Height);

public:
    // Init & Clear Buffer
    void ClearBuffer();

    // Draw Character/String on the Buffer
    void DrawChar(int X, int Y, char Ch);
    void DrawString(int X, int Y, const std::string& Str);

    // Draw Game Border
    void DrawBorder();

    // Render Buffer on Console
    void Render();

    // Get Buffer Size
    int GetWidth() const { return Width; }
    int GetHeight() const { return Height; }

private:
    int Width;
    int Height;

    std::vector<std::vector<char>> Buffer;

    class ConsoleManager* Console;
};
