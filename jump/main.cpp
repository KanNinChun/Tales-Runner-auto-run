#include <iostream>
#include <Windows.h>
#define DEBUG

void _PressCtrlKey()
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
    Sleep(380); // Sleep 380 milliseconds before key up

    // Release Ctrl key
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}


void _PressWKey()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE;
    ip.ki.wScan = MapVirtualKey('W', MAPVK_VK_TO_VSC); // Scan for 'W' key

    // Press 'W' key
    SendInput(1, &ip, sizeof(INPUT));
}

void ReleaseWKey()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    // Release Ctrl key
    SendInput(1, &ip, sizeof(INPUT));
}

void _combain()
{
    _PressWKey();
    _PressCtrlKey();
}

void ResizeWindow(HWND hwnd, int width, int height)
{
    // Set the new position and size of the window
    SetWindowPos(hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

bool handlecheck(HWND targetwindow)
{
    if (targetwindow == NULL)
    {
        std::cerr << "[ERROR] -> Failed to find Tales Runner window." << std::endl;
        return 1; // Error code 1
    }
   
    system("cls");
    std::cout << "[+]\tTales Runner already found !" << std::endl;
    Sleep(700);
    system("cls");
    std::cout << "[+]\tPress X to start!" << std::endl;
    return 0;
}

int main()
{
    bool pressed = false;
    bool previouslyPressed = false;

      HWND targetWindow = FindWindowA(NULL, "Tales Runner"); // Replace "Window Title" with the title of your target window
      handlecheck(targetWindow);

    while (true) {
        SetForegroundWindow(targetWindow); // Bring the target window to the foreground
        #ifdef DEBUG
            ResizeWindow(targetWindow, 500, 500);
        #endif // DEBUG

  
        if (GetAsyncKeyState('X') & 0x8000) {
            if (!previouslyPressed) {
                pressed = !pressed;

            #ifdef DEBUG
                std::cout << "Pressed: " << pressed << std::endl;
            #endif
            }
            previouslyPressed = true;
            SetForegroundWindow(targetWindow); // Bring the target window to the foreground
        }
        else {
            previouslyPressed = false;
            ReleaseWKey(); 
            
        }

       if(pressed && GetForegroundWindow() == targetWindow)
       {
           _combain();
       }

       if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
       {
           
           ResizeWindow(targetWindow, 1000, 900);
           exit(1);
       }

        Sleep(20); // The cpu usage will be optimized, without it will have > 20 CPU usage
       
    }

    return 0;
}