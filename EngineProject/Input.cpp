#include "Input.h"

bool FInput::IsMouseDown(EMouseButton MouseCode)
{
    return bMouseStates[static_cast<int>(MouseCode)];
}

bool FInput::IsMousePressed(EMouseButton MouseCode)
{
    unsigned int Index = static_cast<unsigned int>(MouseCode);
    return bMouseStates[Index] && !bPrevMouseStates[Index];
}

bool FInput::IsMouseReleased(EMouseButton MouseCode)
{
    unsigned int Index = static_cast<unsigned int>(MouseCode);
    return !bMouseStates[Index] && bPrevMouseStates[Index];
}

bool FInput::IsKeyDown(EKeyCode KeyCode)
{
    return bKeyStates[static_cast<int>(KeyCode)];
}

bool FInput::IsKeyPressed(EKeyCode KeyCode)
{
    unsigned int Index = static_cast<unsigned int>(KeyCode);
    return bKeyStates[Index] && !bPrevKeyStates[Index];
}

bool FInput::IsKeyReleased(EKeyCode KeyCode)
{
    unsigned int Index = static_cast<unsigned int>(KeyCode);
    return !bKeyStates[Index] && bPrevKeyStates[Index];
}

void FInput::SetKeyDown(int VirtualKey, bool bIsDown)
{
    if (VirtualKey < 256)
    {
        bKeyStates[VirtualKey] = bIsDown;
    }
}

void FInput::SetMouseButtonDown(EMouseButton MouseCode, bool bIsDown)
{
    unsigned int Index = static_cast<int>(MouseCode);
    if (Index < 5)
    {
        bMouseStates[Index] = bIsDown;
    }
}

void FInput::UpdateInputStates()
{
    std::memcpy(bPrevKeyStates, bKeyStates, sizeof(bKeyStates));
    std::memcpy(bPrevMouseStates, bMouseStates, sizeof(bMouseStates));
}