#include <windows.h>
#include "yuhanCG.h"


bool BonoBonoOn = false;                // 보노보노 너구리를 나타내는 변수
bool EyeType = false;
bool RyanOn = false;                    // 카카오의 들짐승
bool isMouseLButtonPressed = false;     // 마우스 왼쪽이 눌러져있나
bool isMouseInDraw = false;             // 마우스가 드로잉 영역에 있는가

POINT drawstart, drawend;               // 그림 그려지는 영역
POINT startPoint = { 0 };
POINT endPoint = { 0 };
int box_position_x = 10, box_position_y = 10;
int left, top, right, bottom;

#pragma once
void Initialize() {
    isMouseLButtonPressed = false;
}
void ClearView(HWND hWnd, HDC hdc)
{
    //HDC hdc = GetDC(hWnd);
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    InvalidateRect(hWnd, &rcClient, TRUE);
    FillRect(hdc, &rcClient, (HBRUSH)(COLOR_WINDOW + 1));
    //ReleaseDC(hWnd, hdc);
    UpdateWindow(hWnd);

}
// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    
    switch (message) {
    case WM_CREATE:
    {
        Initialize();
        return 0;
    }
    case WM_KEYDOWN:
        if ((wParam == VK_SPACE)) {
            
            EyeType = 1;

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_KEYUP:
        if ((wParam == VK_SPACE)) {
            
            EyeType = 0;

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONDOWN:
        isMouseLButtonPressed = true;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        break;
    
    case WM_LBUTTONUP:
    {
        
        if (isMouseLButtonPressed && RyanOn) {
            isMouseLButtonPressed = false;
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            
        }
        break;
    }
    
     /*버튼 누르면 작동.*/
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {

            BonoBonoOn = false;
            RyanOn = false;
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        if (LOWORD(wParam) == 2) {
            BonoBonoOn = false;
            RyanOn = false;
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        if (LOWORD(wParam) == 3) {
            BonoBonoOn = true;
            RyanOn = false;
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        if (LOWORD(wParam) == 4) {
            BonoBonoOn = false;
            RyanOn = true;
            SetFocus(hWnd);
            left = 0;
            top = 0;
            right = 0;
            bottom = 0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        if (LOWORD(wParam) == 5) {
            BonoBonoOn = false;
            RyanOn = false;
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
    }
    case WM_MOUSEMOVE:

        POINT mousePos;
        GetCursorPos(&mousePos);

        if (mousePos.x >= drawstart.x && mousePos.x <= drawend.x &&
            mousePos.y >= drawstart.y && mousePos.y <= drawend.y) {
            isMouseInDraw = TRUE; // 드로잉 영역 내에 마우스가 있음
            SetCursor(LoadCursor(NULL, IDC_CROSS));
        }
        else {
            isMouseInDraw = FALSE; // 드로잉 영역 밖에 마우스가 있음
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_PAINT: 
        if (true) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);

        int margin = 8;
        int boxWidth = clientRect.right - clientRect.left - 2 * margin;
        int boxHeight = clientRect.bottom - clientRect.top - 2 * margin;

        HBRUSH hColorBrush = CreateSolidBrush(RGB(255, 240, 200));  // 원하는 색상의 브러시 생성
        SelectObject(hdc, hColorBrush);

        int left = margin;
        int top = margin;
        int right = left + boxWidth;
        int bottom = top + boxHeight;

        Rectangle(hdc, left, top, right, bottom);

        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, whiteBrush);
        Rectangle(hdc, left + 8, top + 88, right - 8, bottom - 8);
        drawstart.x = left + 8;
        drawstart.y = top + 88;
        drawend.x = right - 8;
        drawend.y = bottom - 8;


        if (BonoBonoOn) {
            DrawBonobono(hWnd, hdc, EyeType);

        }
        if (RyanOn && isMouseLButtonPressed) {
            MoveToEx(hdc, startPoint.x, startPoint.y, NULL);

            int left = startPoint.x;
            int top = startPoint.y;
            int right = endPoint.x;
            int bottom = endPoint.y;
            DrawRyan(hWnd, hdc, left, top, right, bottom);

        }
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 프로그램 진입점
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hWnd, hwndbox1, hwndbox2;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;
    HDC hdc; // hdc 선언
    int left, top, right, bottom;

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));    //백그라운드 색
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("201807058정의찬");
    wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        return 1;
    }

    hWnd = CreateWindow(
        wc.lpszClassName, TEXT("201807058정의찬"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        0, 0, 800, 480, NULL, NULL, hInstance, NULL);

    

    if (!hWnd) {
        return FALSE;
    }

    int bstart = 32; //Button1 x좌표 시작지점
    int bmargin = 146;
    hButton1 = CreateWindow(
        L"BUTTON", L"BOX", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        bstart, 16, 130, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        bstart + bmargin, 16, 130, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        bstart + bmargin * 2, 16, 130, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        bstart + bmargin * 3, 16, 130, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        bstart + bmargin * 4, 16, 130, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }

    return (int)msg.wParam;
}