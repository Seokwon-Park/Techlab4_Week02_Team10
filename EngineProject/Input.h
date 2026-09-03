#pragma once

#include "KeyCode.h"
#include "MouseButton.h"
#include "Types.h"

class FInput
{
public:
    static bool IsKeyPressed(EKeyCode KeyCode);
    static bool IsKeyReleased(EKeyCode KeyCode);
    static bool IsKeyDown(EKeyCode KeyCode);

    static bool IsMouseDown(EMouseButton MouseButton);
    static bool IsMousePressed(EMouseButton MouseButton);
    static bool IsMouseReleased(EMouseButton MouseButton);

    static void UpdateInputStates();
    static void SetKeyDown(int VirtualKey, bool bIsDown);
    static void SetMouseButtonDown(EMouseButton MouseButton, bool bIsDown);

private:
    FInput() = delete;

    static inline bool bMouseStates[5] = {};
    static inline bool bPrevMouseStates[5] = {};

    static inline bool bKeyStates[256] = {};
    static inline bool bPrevKeyStates[256] = {};

    static inline int32 MouseX = 0, MouseY = 0;
    static inline int32 LastMouseX = 0, LastMouseY = 0;
    static inline int32 DeltaX = 0, DeltaY = 0;

    
};