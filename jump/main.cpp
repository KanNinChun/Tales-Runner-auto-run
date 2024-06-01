#include <iostream>
#include <Windows.h>
#define DEBUG

void PressCtrlKey()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE;
    ip.ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC); // Scan for CTRL KEY

    // Press Ctrl key
    SendInput(1, &ip, sizeof(INPUT));
    Sleep(380); // Sleep 400 milliseconds before key up

    // Release Ctrl key
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

INPUT wip;
void _PressWKey()
{
    wip.type = INPUT_KEYBOARD;
    wip.ki.wVk = 0;
    wip.ki.dwFlags = KEYEVENTF_SCANCODE;
    wip.ki.wScan = MapVirtualKey('W', MAPVK_VK_TO_VSC); // Scan for 'W' key

    // Press 'W' key
    SendInput(1, &wip, sizeof(INPUT));
}

void _jumpDelay()
{
    PressCtrlKey();
}

void _combain()
{
    _PressWKey();
    _jumpDelay();
}

int main()
{
    bool pressed = false;
    bool previouslyPressed = false;

    #ifdef DEBUG
        std::cout << "Pressed: " << pressed << std::endl;
    #endif

    while (true) {
        if (GetAsyncKeyState('X') & 0x8000) {
            if (!previouslyPressed) {
                pressed = !pressed;

            #ifdef DEBUG
                std::cout << "Pressed: " << pressed << std::endl;
            #endif

            }
            previouslyPressed = true;
        }
        else {
            previouslyPressed = false;

            // Release 'W' key
            wip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
            SendInput(1, &wip, sizeof(INPUT));
        }

       if(pressed)
       {
           _combain();
       }
        Sleep(20); // The cpu usage will be optimized, without it will have > 20 CPU usage
        
    }

    return 0;
}