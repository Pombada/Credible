#include <windows.h>
#include <cstring>
#include "logic.h"
HWND hEdit;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_CREATE: {
        RECT rect;
        GetClientRect(hwnd, &rect);

        int centerX = (rect.right - rect.left) / 2;

        // Input box (centered)
        hEdit = CreateWindowEx(
            0, "EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            centerX - 100, 80, 200, 25,
            hwnd, NULL, NULL, NULL
        );

        SendMessage(hEdit, EM_SETLIMITTEXT, 19, 0);

        // Button (centered under input)
        CreateWindow(
            "BUTTON", "Generate",
            WS_VISIBLE | WS_CHILD,
            centerX - 50, 120, 100, 30,
            hwnd, (HMENU)1, NULL, NULL
        );
        break;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            char buffer[32];
            GetWindowText(hEdit, buffer, sizeof(buffer));

            if (strlen(buffer)>= 12 && strlen(buffer)<=19) {
                if (Luhn_algorithm(buffer)) MessageBox(hwnd, "This is a real credit card!", "Credible!", MB_OK);
                else {
                    MessageBox(hwnd, "The following credit card number doesn't exist!", "Non-Credible :(", MB_OK);
                }
            } else {
                MessageBox(hwnd, "Must be at least 12 digits!", "Error", MB_OK);
            }
        }
            break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {

    const char CLASS_NAME[] = "CenteredApp";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // 🟢 Get screen size
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 🟢 Window size
    int winWidth = 400;
    int winHeight = 250;

    // 🟢 Center position
    int posX = (screenWidth - winWidth) / 2;
    int posY = (screenHeight - winHeight) / 2;

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Enter Credit Card Number",
        WS_OVERLAPPEDWINDOW,
        posX, posY, winWidth, winHeight,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}