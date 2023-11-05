#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <wchar.h>
#include <winuser.h>

#define KEY_DOWN(vk_key) (( GetAsyncKeyState(vk_key) & 0x8001 )? 1:0)
#define KEY_UP(vk_key)   (( GetAsyncKeyState(vk_key) & 0x8001 )? 0:1)

// 보노보노 너구리&^^를 나타내는 변수
bool BonoBonoOn = false;
bool EyeType = false;
int box_position_x = 10, box_position_y = 10;

// 박스 그리기 함수
void DrawBonobono(HWND hWnd, HDC hdc, BOOL EyeType) {   // EyeType = 0 : 0o0, 1 : >o<
    RECT rect;
    GetClientRect(hWnd, &rect);

    // 파란너구리 = true
    if (BonoBonoOn) {
        // 박스 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // 파란색
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 240, 120, 560, 400);
        // 파란 너구리의 입을 그리기 위해 색을 핑크색으로 바꿈
        hBrush = CreateSolidBrush(RGB(255, 150, 255));      // 핑크 맞음
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 380, 270, 420, 330);
        // 눈뜨기 눈감기 구현
        // 눈 그리기                            /// >< 눈감은거 구현해야함
        if (!EyeType)
        {
            // 눈떠
            hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 270, 240, 280, 260);
            Ellipse(hdc, 520, 240, 530, 260);

            hBrush = CreateSolidBrush(RGB(255, 255, 255)); // white
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 272, 242, 278, 250);
            Ellipse(hdc, 522, 242, 528, 250);
        }
        else
        {
            //보노보노 폐사시키는 코드
            //hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
            //SelectObject(hdc, hBrush);
            //MoveToEx(hdc, 270, 240, NULL);
            //LineTo(hdc, 285, 250);
            //MoveToEx(hdc, 270, 250, NULL);
            //LineTo(hdc, 285, 240);

            //MoveToEx(hdc, 515, 240, NULL);
            //LineTo(hdc, 530, 250);
            //MoveToEx(hdc, 515, 250, NULL);
            //LineTo(hdc, 530, 240);
            hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
            SelectObject(hdc, hBrush);
            MoveToEx(hdc, 270, 240, NULL);
            LineTo(hdc, 285, 245);
            MoveToEx(hdc, 270, 250, NULL);
            LineTo(hdc, 285, 245);

            MoveToEx(hdc, 515, 245, NULL);
            LineTo(hdc, 530, 240);
            MoveToEx(hdc, 515, 245, NULL);
            LineTo(hdc, 530, 250);

        }
        // 보노보노의 귀여운 주둥이
        hBrush = CreateSolidBrush(RGB(255, 255, 255)); // white
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 350, 255, 400, 300);
        Ellipse(hdc, 400, 255, 450, 300);
        // 수염
        hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
        SelectObject(hdc, hBrush);
        MoveToEx(hdc, 330, 260, NULL);
        LineTo(hdc, 370, 270);

        MoveToEx(hdc, 330, 290, NULL);
        LineTo(hdc, 370, 280);

        MoveToEx(hdc, 430, 270, NULL);
        LineTo(hdc, 470, 260);

        MoveToEx(hdc, 430, 280, NULL);
        LineTo(hdc, 470, 290);
        // 노즈
        hBrush = CreateSolidBrush(RGB(0, 0, 0)); // black
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 380, 240, 420, 275);

        DeleteObject(hBrush);
    }
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HBRUSH hBrush;
    switch (message) {
    case WM_ERASEBKGND: // 배경을 지우기 전 호출
    {
        HDC hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);

        
        HBRUSH hbr = CreateSolidBrush(RGB(255, 240, 200));
        FillRect(hdc, &rect, hbr);
        DeleteObject(hbr);

        return 1; // 처리 완료
    }
    // 버튼 누르면 작동.
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 1:
            BonoBonoOn = false;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 3:
            BonoBonoOn = true;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawBonobono(hWnd, hdc, EyeType);
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

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("Computer Science");
    wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        return 1;
    }

    hWnd = CreateWindow(
        wc.lpszClassName, TEXT("201807058정의찬"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
        0, 0, 800, 480, NULL, NULL, hInstance, NULL);

    //--박스1 선언
    hwndbox1 = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"",      // Button text 
        WS_VISIBLE | WS_CHILD | BS_GROUPBOX, // BS_GROUPBOX 
        box_position_x,         // x position 
        box_position_y,         // y position 
        765,        // Button width
        420,        // Button height
        hWnd,     // Parent window
        (HMENU)0xF1,       // No menu. -> button 0
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    //

    //--그림영역 선언
    hwndbox2 = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"",      // Button text 
        WS_VISIBLE | WS_CHILD | BS_GROUPBOX, // BS_GROUPBOX 
        box_position_x + 8,         // x position 
        box_position_y + 84,         // y position 
        749,        // Button width
        325,        // Button height
        hWnd,     // Parent window
        (HMENU)0xF1,       // No menu. -> button 0
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    //

    if (!hWnd) {
        return FALSE;
    }
    if (!hwndbox1) {
        return FALSE;
    }
    if (!hwndbox2) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"BOX", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        22, 24, 135, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        174, 24, 135, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        326, 24, 135, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        478, 24, 135, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        630, 24, 135, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        hdc = GetDC(hWnd);

        switch (msg.message)
        {
        case WM_KEYDOWN:
            if (KEY_DOWN(VK_SPACE))
            {
                DrawBonobono(hWnd, hdc, TRUE);
            }
            break;
        case WM_KEYUP:
            if (KEY_UP(VK_SPACE))
            {
                DrawBonobono(hWnd, hdc, FALSE);
            }
            break;
        }

        ReleaseDC(hWnd, hdc); // hdc를 해제
    }

    return (int)msg.wParam;
}
